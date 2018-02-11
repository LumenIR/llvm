//===-- LumenIRTargetMachine.h - Define TargetMachine for LumenIR ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the LumenIR specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LUMENIR_LUMENIRTARGETMACHINE_H
#define LLVM_LIB_TARGET_LUMENIR_LUMENIRTARGETMACHINE_H

#include "LumenIRSubtarget.h"

#include "MCTargetDesc/LumenIRMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class LumenIRTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  LumenIRTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  const LumenIRSubtarget *getSubtargetImpl() const;
  const LumenIRSubtarget *getSubtargetImpl(const Function &) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

private:
  LumenIRSubtarget SubTarget;
};
}

#endif
