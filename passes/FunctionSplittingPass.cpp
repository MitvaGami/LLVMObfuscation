#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <random>
#include <vector>

using namespace llvm;

struct FunctionSplittingPass : public PassInfoMixin<FunctionSplittingPass> {
private:
    std::mt19937 rng;
    int split_count = 0;
    
    bool shouldSplit(Function& F) {
        // Only split functions with a decent number of basic blocks
        return F.size() > 5 && F.getInstructionCount() > 30 && !F.isDeclaration();
    }
    
    void splitFunction(Function& F) {
        LLVMContext& ctx = F.getContext();
        
        std::vector<BasicBlock*> blocks;
        for (BasicBlock& BB : F) {
            blocks.push_back(&BB);
        }
        
        // Find a random split point in the middle of the function
        if (blocks.size() < 4) return;
        size_t splitPointIdx = (blocks.size() / 2) + (rng() % (blocks.size() / 4));
        BasicBlock* splitPointBB = blocks[splitPointIdx];

        // Create the new function for the second half
        FunctionType* splitFuncType = FunctionType::get(Type::getVoidTy(ctx), false);
        Function* splitFunc = Function::Create(
            splitFuncType, Function::InternalLinkage, F.getName() + "_split", F.getParent()
        );

        // Move all basic blocks from the split point to the end into the new function
        std::vector<BasicBlock*> blocksToMove;
        for (size_t i = splitPointIdx; i < blocks.size(); ++i) {
            blocksToMove.push_back(blocks[i]);
        }
        for (BasicBlock* BB : blocksToMove) {
            BB->removeFromParent();
            BB->insertInto(splitFunc);
        }
        
        // The block before the split point needs to call our new function
        BasicBlock* predecessor = blocks[splitPointIdx - 1];
        predecessor->getTerminator()->eraseFromParent();
        IRBuilder<> builder(predecessor);
        builder.CreateCall(splitFunc);
        
        // If the original function returned a value, we need to add a return here.
        // This simplified version assumes the split happens before the return,
        // so we add a default return. A more complex pass would need to handle this better.
        if (F.getReturnType()->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            builder.CreateRet(Constant::getNullValue(F.getReturnType()));
        }

        // The old return instructions are now in the split function.
        // We need to change them to void returns.
        for (BasicBlock* BB : blocksToMove) {
            if (ReturnInst* RI = dyn_cast<ReturnInst>(BB->getTerminator())) {
                IRBuilder<> retBuilder(RI);
                retBuilder.CreateRetVoid();
                RI->eraseFromParent();
            }
        }
        
        split_count++;
    }
    
public:
    FunctionSplittingPass() : rng(std::random_device{}()) {}
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        split_count = 0;
        
        std::vector<Function*> functionsToSplit;
        for (Function& F : M) {
            if (shouldSplit(F)) {
                functionsToSplit.push_back(&F);
            }
        }
        
        for (Function* F : functionsToSplit) {
            splitFunction(*F);
        }
        
        errs() << "FunctionSplittingPass: Split " << split_count << " functions\n";
        return PreservedAnalyses::none();
    }
};

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "FunctionSplittingPass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "func-split") {
                            MPM.addPass(FunctionSplittingPass());
                            return true;
                        }
                        return false;
                    });
            }};
}

