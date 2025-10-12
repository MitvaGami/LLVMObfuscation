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

using namespace llvm;

struct AdvancedBogusPass : public PassInfoMixin<AdvancedBogusPass> {
private:
    std::mt19937 rng;
    int bogus_count = 0;
    
    enum BogusType {
        ARITHMETIC_CHAIN,
        CONDITIONAL_NOISE,
        MEMORY_OPERATIONS
    };
    
    void insertArithmeticChain(IRBuilder<>& builder, LLVMContext& ctx) {
        Value* x = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 100);
        Value* y = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 100);
        Value* add = builder.CreateAdd(x, y);
        Value* mul = builder.CreateMul(add, ConstantInt::get(Type::getInt32Ty(ctx), 2));
        Value* sub = builder.CreateSub(x, y);
        builder.CreateXor(mul, sub);
        bogus_count += 4;
    }
    
    void insertConditionalNoise(IRBuilder<>& builder, BasicBlock* BB) {
        Value* alwaysFalse = builder.CreateICmpEQ(
            ConstantInt::get(Type::getInt32Ty(BB->getContext()), 1),
            ConstantInt::get(Type::getInt32Ty(BB->getContext()), 0)
        );
        
        BasicBlock* continueBB = BB->splitBasicBlock(builder.GetInsertPoint(), "continue");
        BasicBlock* fakeBB = BasicBlock::Create(BB->getContext(), "fake_branch", BB->getParent(), continueBB);

        BB->getTerminator()->eraseFromParent();
        
        builder.SetInsertPoint(BB);
        builder.CreateCondBr(alwaysFalse, fakeBB, continueBB);
        
        builder.SetInsertPoint(fakeBB);
        insertArithmeticChain(builder, BB->getContext());
        builder.CreateBr(continueBB);
        
        builder.SetInsertPoint(continueBB, continueBB->begin());
        bogus_count += 2;
    }
    
    void insertMemoryOperations(IRBuilder<>& builder, LLVMContext& ctx) {
        AllocaInst* fakeAlloca = builder.CreateAlloca(Type::getInt32Ty(ctx), nullptr, "fake_mem");
        Value* val = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 1000);
        builder.CreateStore(val, fakeAlloca);
        builder.CreateLoad(Type::getInt32Ty(ctx), fakeAlloca);
        bogus_count += 3;
    }
    
public:
    AdvancedBogusPass() : rng(std::random_device{}()) {}
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        bogus_count = 0;
        
        std::vector<Instruction*> insertion_points;
        for (Function &F : M) {
            if (F.isDeclaration()) continue;
            
            for (BasicBlock &BB : F) {
                // BUG FIX: Do not insert bogus code in blocks that return.
                // This prevents the corruption of function exit points.
                if (isa<ReturnInst>(BB.getTerminator())) {
                    continue;
                }
                // Also avoid blocks that are targets of exceptions or other complex control flow.
                if (!BB.getTerminator()->isTerminator()) {
                    continue;
                }

                // Add bogus code to the middle of the block for variety.
                if (BB.size() > 2) {
                   insertion_points.push_back(&*std::next(BB.begin(), BB.size() / 2));
                } else {
                   insertion_points.push_back(&*BB.begin());
                }
            }
        }
        
        for (Instruction* I : insertion_points) {
            IRBuilder<> builder(I);
            
            BogusType type = static_cast<BogusType>(rng() % 3);
            
            switch (type) {
                case ARITHMETIC_CHAIN:
                    insertArithmeticChain(builder, M.getContext());
                    break;
                case CONDITIONAL_NOISE:
                    insertConditionalNoise(builder, I->getParent());
                    break;
                case MEMORY_OPERATIONS:
                    insertMemoryOperations(builder, M.getContext());
                    break;
            }
        }
        
        errs() << "AdvancedBogusPass: Added " << bogus_count << " bogus instructions\n";
        return PreservedAnalyses::none();
    }
};

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "AdvancedBogusPass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "advanced-bogus") {
                            MPM.addPass(AdvancedBogusPass());
                            return true;
                        }
                        return false;
                    });
            }};
}
