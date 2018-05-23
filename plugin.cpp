#include "RangeAnalysis.h"

#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Transforms/Scalar.h>

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#include<iostream>

int main(int argc, char **argv) {
 // LLVMContext &Context = getGlobalContext();
  static LLVMContext Context;
  SMDiagnostic Err;

  // Load the input module
  std::unique_ptr<Module> M = parseIRFile(argv[1], Err, Context);
  if (!M) {
    Err.print(argv[0], errs());
    return 1;
  }

  IntraProceduralRA ra;
  for (auto& f : *M) {
      auto CG = ra.run(f);
      //CG.printResultIntervals();
      /*for (auto& v : CG.vars)
      {
          llvm::errs()<<*(v.first);
         llvm::errs()<<v.second->getRange().getUpper().roundToDouble(true) <<"\n";
      }*/
      for (auto& BB : f) {
          for (auto& ins : BB) {
              if (auto* boInst = dyn_cast<BinaryOperator>(&ins)) {
                  Value* op1 = boInst->getOperand(0);
                  Value* op2 = boInst->getOperand(1);
                  Range r1 = CG.getRange(op1);
                  Range r2 = CG.getRange(op2);
                  llvm::errs()<< *op1 << "\n";
                  r1.print(errs());
                  llvm::errs()<< "\n";
                  llvm::errs()<< *op2 << "\n";
                  r2.print(errs());
                  llvm::errs()<< "\n";
              }
          }
      }
  }

}
