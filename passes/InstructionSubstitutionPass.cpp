#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <random>

using namespace llvm;

namespace {
struct InstructionSubstitutionPass : public PassInfoMixin<InstructionSubstitutionPass> {
  unsigned NumSubs = 0;

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    std::mt19937 rng{std::random_device{}()};

    for (Function &F : M) {
      if (F.isDeclaration()) continue;
      for (BasicBlock &BB : F) {
        for (auto It = BB.begin(); It != BB.end(); ) {
          Instruction *I = &*It++;
          if (auto *BinOp = dyn_cast<BinaryOperator>(I)) {
            IRBuilder<> B(BinOp);
            // Replace add x, y with sub x, (0 - y) as a simple semantics-preserving tweak
            if (BinOp->getOpcode() == Instruction::Add && BinOp->getType()->isIntegerTy()) {
              Value *Y = BinOp->getOperand(1);
              if (isa<Constant>(Y) || isa<Instruction>(Y)) {
                Value *Zero = ConstantInt::get(BinOp->getType(), 0);
                Value *NegY = B.CreateSub(Zero, Y, "neg.tmp");
                Value *NewV = B.CreateSub(BinOp->getOperand(0), NegY, "sub.subst");
                BinOp->replaceAllUsesWith(NewV);
                BinOp->eraseFromParent();
                ++NumSubs;
                continue;
              }
            }
          }
        }
      }
    }

    if (NumSubs > 0) {
      errs() << "InstructionSubstitution: Applied " << NumSubs << " substitutions\n";
      return PreservedAnalyses::none();
    }
    return PreservedAnalyses::all();
  }
};
} // namespace

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "InstructionSubstitutionPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "inst-subst") {
                    MPM.addPass(InstructionSubstitutionPass());
                    return true;
                  }
                  return false;
                });
          }};
}


