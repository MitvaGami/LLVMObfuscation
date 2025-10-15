#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <random>

using namespace llvm;

struct OpaquePredicatePass : public PassInfoMixin<OpaquePredicatePass> {
private:
    std::mt19937 rng;
    int predicate_count = 0;
    
    // Mathematical properties that are always true/false but hard to analyze
    Value* createAlwaysTrue(IRBuilder<>& builder, LLVMContext& ctx) {
        // (x^2 + y^2) >= 2*x*y  (always true due to (x-y)^2 >= 0)
        Value* x = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 100 + 1);
        Value* y = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 100 + 1);
        
        Value* x_sq = builder.CreateMul(x, x);
        Value* y_sq = builder.CreateMul(y, y);
        Value* left = builder.CreateAdd(x_sq, y_sq);
        
        Value* two = ConstantInt::get(Type::getInt32Ty(ctx), 2);
        Value* xy = builder.CreateMul(x, y);
        Value* right = builder.CreateMul(two, xy);
        
        return builder.CreateICmpSGE(left, right);
    }
    
    Value* createAlwaysFalse(IRBuilder<>& builder, LLVMContext& ctx) {
        // x^2 + 1 == 0 (never true for real integers)
        Value* x = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 100);
        Value* x_sq = builder.CreateMul(x, x);
        Value* x_sq_plus_1 = builder.CreateAdd(x_sq, ConstantInt::get(Type::getInt32Ty(ctx), 1));
        
        return builder.CreateICmpEQ(x_sq_plus_1, ConstantInt::get(Type::getInt32Ty(ctx), 0));
    }
    
    Value* createComplexPredicate(IRBuilder<>& builder, LLVMContext& ctx) {
        // Modular arithmetic: (a*b) % n == ((a%n) * (b%n)) % n
        Value* a = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 50 + 1);
        Value* b = ConstantInt::get(Type::getInt32Ty(ctx), rng() % 50 + 1);
        Value* n = ConstantInt::get(Type::getInt32Ty(ctx), 7); // Small prime
        
        Value* ab = builder.CreateMul(a, b);
        Value* left = builder.CreateSRem(ab, n);
        
        Value* a_mod_n = builder.CreateSRem(a, n);
        Value* b_mod_n = builder.CreateSRem(b, n);
        Value* ab_mod = builder.CreateMul(a_mod_n, b_mod_n);
        Value* right = builder.CreateSRem(ab_mod, n);
        
        return builder.CreateICmpEQ(left, right);
    }
    
public:
    OpaquePredicatePass() : rng(std::random_device{}()) {}
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        predicate_count = 0;
        
        for (Function &F : M) {
            if (F.isDeclaration()) continue;
            
            std::vector<BasicBlock*> blocks;
            for (BasicBlock &BB : F) {
                blocks.push_back(&BB);
            }
            
            for (BasicBlock* BB : blocks) {
                if (BB->size() < 2) continue; // Skip small blocks
                
                // Insert opaque predicate in middle of block
                auto insertPoint = BB->begin();
                std::advance(insertPoint, BB->size() / 2);
                
                IRBuilder<> builder(BB, insertPoint);
                LLVMContext& ctx = M.getContext();
                
                // Create predicate based on random choice
                Value* predicate;
                int choice = rng() % 3;
                switch (choice) {
                    case 0:
                        predicate = createAlwaysTrue(builder, ctx);
                        break;
                    case 1:
                        predicate = createAlwaysFalse(builder, ctx);
                        break;
                    default:
                        predicate = createComplexPredicate(builder, ctx);
                }
                
                // Split block and create conditional branch
                BasicBlock* continueBB = BB->splitBasicBlock(insertPoint, "opaque_continue");
                BasicBlock* fakeBB = BasicBlock::Create(ctx, "opaque_fake", &F);
                
                // Remove the unconditional branch created by splitBasicBlock
                BB->getTerminator()->eraseFromParent();
                
                builder.SetInsertPoint(BB);
                if (choice == 1) { // Always false
                    builder.CreateCondBr(predicate, fakeBB, continueBB);
                } else { // Always true or complex
                    builder.CreateCondBr(predicate, continueBB, fakeBB);
                }
                
                // Add bogus code to fake branch
                builder.SetInsertPoint(fakeBB);
                Value* bogus = builder.CreateAdd(
                    ConstantInt::get(Type::getInt32Ty(ctx), 42),
                    ConstantInt::get(Type::getInt32Ty(ctx), 58)
                );
                builder.CreateBr(continueBB);
                
                predicate_count++;
            }
        }
        
        errs() << "OpaquePredicatePass: Added " << predicate_count << " opaque predicates\n";
        return PreservedAnalyses::none();
    }
};

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "OpaquePredicatePass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "opaque-pred") {
                            MPM.addPass(OpaquePredicatePass());
                            return true;
                        }
                        return false;
                    });
            }};
}
