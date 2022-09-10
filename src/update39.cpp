#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

struct Update39 : PassInfoMixin<Update39> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    bool changed = false;
    for (Function::iterator BB = F.begin(); BB != F.end(); BB++) {
     for (BasicBlock::iterator I = BB->begin(); I != BB->end(); I++) {
        if (I->getOpcode() == Instruction::Add &&
            I->getOperand(0) == ConstantInt::get(I->getOperand(0)->getType(), 39)) {
          Instruction *J = BinaryOperator::CreateMul(I->getOperand(0), I->getOperand(1));
          ReplaceInstWithInst(BB->getInstList(), I, J);
          changed = true;
          errs() << "(llvm-update39) `39 + _` to `39 * _` in " << F.getName() << "\n";
        }
      }
    }
    return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }
  static bool isRequired() { return true; }
};

llvm::PassPluginLibraryInfo getUpdate39PluginInfo() {
  static int done = 0;
  return {LLVM_PLUGIN_API_VERSION, "Update39", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
              [](ModulePassManager &MPM, llvm::OptimizationLevel Level) {
                 FunctionPassManager FPM;
                 FPM.addPass(Update39());
                 MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
            });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getUpdate39PluginInfo();
}
