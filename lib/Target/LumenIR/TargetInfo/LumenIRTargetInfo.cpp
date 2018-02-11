//===-- LumenIRTargetInfo.cpp - LumenIR Target Implementation ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

namespace llvm {
Target &getTheLumenIRTarget() {
  static Target TheLumenIRTarget;
  return TheLumenIRTarget;
}
}

extern "C" void LLVMInitializeLumenIRTargetInfo() {
  RegisterTarget<Triple::lumenir> X(getTheLumenIRTarget(), "lumenir",
                                    "LumenIR");
}

