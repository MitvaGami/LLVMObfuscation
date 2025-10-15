#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <random>
#include <vector>
#include <map>
#include <algorithm>

using namespace llvm;

struct CFFlattening : public PassInfoMixin<CFFlattening> {
private:
    std::mt19937 rng;
    int flattened_count = 0;
    
    bool shouldFlatten(Function& F) {
        if (F.size() <= 2 || F.isDeclaration() || !F.hasExactDefinition()) {
            return false;
        }

        // Skip functions that already have switch statements or are too complex
        for (BasicBlock& BB : F) {
            if (isa<SwitchInst>(BB.getTerminator())) {
                errs() << "CFFlattening: Skipping function " << F.getName() << " due to switch statement.\n";
                return false;
            }
            // Skip functions with invoke instructions (exception handling)
            for (Instruction& I : BB) {
                if (isa<InvokeInst>(&I)) {
                    errs() << "CFFlattening: Skipping function " << F.getName() << " due to invoke instruction.\n";
                    return false;
                }
            }
        }

        return true;
    }
    
    void flattenFunction(Function& F) {
        LLVMContext& ctx = F.getContext();
        
        std::vector<BasicBlock*> originalBlocks;
        BasicBlock* entryBB = &F.getEntryBlock();
        
        // Collect all blocks except entry
        for (BasicBlock& BB : F) {
            if (&BB != entryBB) {
                originalBlocks.push_back(&BB);
            }
        }
        
        if (originalBlocks.empty()) {
            errs() << "CFFlattening: No blocks to flatten in function " << F.getName() << "\n";
            return;
        }

        entryBB->setName("entry");
        
        // Create dispatcher and return blocks
        BasicBlock* dispatcherBB = BasicBlock::Create(ctx, "dispatcher", &F);
        BasicBlock* returnBB = BasicBlock::Create(ctx, "return_block", &F);
        
        // Find insertion point in entry block
        Instruction* insertPt = entryBB->getFirstNonPHI();
        if (!insertPt) {
            errs() << "CFFlattening: No valid insertion point in entry block\n";
            return;
        }
        
        IRBuilder<> entryBuilder(insertPt);
        
        // Create switch variable
        AllocaInst* switchVar = entryBuilder.CreateAlloca(Type::getInt32Ty(ctx), nullptr, "switch_var");
        
        // Create return value storage if needed
        AllocaInst* retValStorage = nullptr;
        if (!F.getReturnType()->isVoidTy()) {
            retValStorage = entryBuilder.CreateAlloca(F.getReturnType(), nullptr, "retval_storage");
        }

        // Assign case numbers to blocks
        std::map<BasicBlock*, int> blockToCaseNum;
        std::vector<int> caseNumbers;
        for (size_t i = 0; i < originalBlocks.size(); ++i) {
            caseNumbers.push_back(i + 1);
        }
        std::shuffle(caseNumbers.begin(), caseNumbers.end(), rng);
        for (size_t i = 0; i < originalBlocks.size(); ++i) {
            blockToCaseNum[originalBlocks[i]] = caseNumbers[i];
        }

        // Modify entry block terminator
        Instruction* origEntryTerminator = entryBB->getTerminator();
        if (!origEntryTerminator) {
            errs() << "CFFlattening: Entry block has no terminator\n";
            return;
        }
        
        entryBuilder.SetInsertPoint(origEntryTerminator);
        
        // Handle entry block's original destination
        if (BranchInst* br = dyn_cast<BranchInst>(origEntryTerminator)) {
            if (!br->isConditional() && br->getNumSuccessors() > 0) {
                BasicBlock* firstOrigBlock = br->getSuccessor(0);
                if (blockToCaseNum.find(firstOrigBlock) != blockToCaseNum.end()) {
                    entryBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), blockToCaseNum[firstOrigBlock]), switchVar);
                } else {
                    entryBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), 0), switchVar);
                }
            } else {
                entryBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), 0), switchVar);
            }
        } else {
            entryBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), 0), switchVar);
        }
        
        entryBuilder.CreateBr(dispatcherBB);
        origEntryTerminator->eraseFromParent();
        
        // Create dispatcher switch
        IRBuilder<> dispatcherBuilder(dispatcherBB);
        Value* loadedSwitchVal = dispatcherBuilder.CreateLoad(Type::getInt32Ty(ctx), switchVar);
        SwitchInst* mainSwitch = dispatcherBuilder.CreateSwitch(loadedSwitchVal, returnBB, originalBlocks.size());
        
        // Add cases for each block
        for (auto const& [bb, caseNum] : blockToCaseNum) {
            mainSwitch->addCase(ConstantInt::get(Type::getInt32Ty(ctx), caseNum), bb);
        }

        // Modify terminators of original blocks
        for (BasicBlock* bb : originalBlocks) {
            Instruction* terminator = bb->getTerminator();
            if (!terminator) continue;
            
            IRBuilder<> termBuilder(terminator);

            if (BranchInst* br_term = dyn_cast<BranchInst>(terminator)) {
                if (br_term->isConditional()) {
                    BasicBlock* trueDest = br_term->getSuccessor(0);
                    BasicBlock* falseDest = br_term->getSuccessor(1);
                    Value* condition = br_term->getCondition();
                    
                    // Find case numbers for destinations
                    int trueCase = 0;
                    int falseCase = 0;
                    
                    if (blockToCaseNum.find(trueDest) != blockToCaseNum.end()) {
                        trueCase = blockToCaseNum.at(trueDest);
                    }
                    if (blockToCaseNum.find(falseDest) != blockToCaseNum.end()) {
                        falseCase = blockToCaseNum.at(falseDest);
                    }
                    
                    Value* trueCaseVal = ConstantInt::get(Type::getInt32Ty(ctx), trueCase);
                    Value* falseCaseVal = ConstantInt::get(Type::getInt32Ty(ctx), falseCase);
                    
                    Value* nextCase = termBuilder.CreateSelect(condition, trueCaseVal, falseCaseVal);
                    termBuilder.CreateStore(nextCase, switchVar);
                } else if (br_term->getNumSuccessors() > 0) {
                    BasicBlock* dest = br_term->getSuccessor(0);
                    int nextCase = 0;
                    if (blockToCaseNum.find(dest) != blockToCaseNum.end()) {
                        nextCase = blockToCaseNum.at(dest);
                    }
                    termBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), nextCase), switchVar);
                }
            } else if (ReturnInst* ret = dyn_cast<ReturnInst>(terminator)) {
                if (ret->getReturnValue() && retValStorage) {
                    termBuilder.CreateStore(ret->getReturnValue(), retValStorage);
                }
                termBuilder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), 0), switchVar);
            }
            
            terminator->eraseFromParent();
            termBuilder.CreateBr(dispatcherBB);
        }

        // Create return block
        IRBuilder<> returnBuilder(returnBB);
        if (F.getReturnType()->isVoidTy()) {
            returnBuilder.CreateRetVoid();
        } else if (retValStorage) {
            Value* finalRetVal = returnBuilder.CreateLoad(F.getReturnType(), retValStorage);
            returnBuilder.CreateRet(finalRetVal);
        } else {
            returnBuilder.CreateRet(Constant::getNullValue(F.getReturnType()));
        }
        
        flattened_count++;
        errs() << "CFFlattening: Successfully flattened function " << F.getName() << "\n";
    }
    
public:
    CFFlattening() : rng(std::random_device{}()) {}
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        flattened_count = 0;
        
        std::vector<Function*> functions;
        for (Function& F : M) {
            if (shouldFlatten(F)) {
                functions.push_back(&F);
            }
        }
        
        for (Function* F : functions) {
            flattenFunction(*F);
        }
        
        errs() << "CFFlattening: Flattened " << flattened_count << " functions\n";
        return PreservedAnalyses::none();
    }
};

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "CFFlattening", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "cf-flatten") {
                            MPM.addPass(CFFlattening());
                            return true;
                        }
                        return false;
                    });
            }};
}
