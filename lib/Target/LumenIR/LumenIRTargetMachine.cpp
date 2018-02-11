//===-- LumenIRTargetMachine.cpp - Define TargetMachine for LumenIR -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about LumenIR target spec.
//
//===----------------------------------------------------------------------===//

#include "LumenIRTargetMachine.h"

#include "LumenIR.h"
#include "LumenIRTargetObjectFile.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

extern "C" void LLVMInitializeLumenIRTarget() {
  RegisterTargetMachine<LumenIRTargetMachine> X(getTheLumenIRTarget());
}

static std::string computeDataLayout(const Triple &TT) {
    return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
    return Reloc::Static;
}

/// Processes a CPU name.
static StringRef getCPU(StringRef CPU) {
  if (CPU.empty() || CPU == "generic") {
    return "lumenir";
  }

  return CPU;
}

LumenIRTargetMachine::LumenIRTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       CodeModel::Model CM,
                                       CodeGenOpt::Level OL)
    : LLVMTargetMachine(T,
                        computeDataLayout(TT),
                        TT,
                        CPU,
                        FS,
                        Options,
                        getEffectiveRelocModel(TT, RM),
                        CM,
                        OL),
      SubTarget(TT, getCPU(CPU), FS, *this),
      TLOF(make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

const LumenIRSubtarget *LumenIRTargetMachine::getSubtargetImpl() const {
  return &SubTarget;
}

const LumenIRSubtarget *LumenIRTargetMachine::getSubtargetImpl(const Function &) const {
  return &SubTarget;
}


//===----------------------------------------------------------------------===//
// Pass Pipeline Configuration
//===----------------------------------------------------------------------===//

namespace {
// LumenIR Code Generator Pass Configuration Options.
class LumenIRPassConfig : public TargetPassConfig {
public:
  LumenIRPassConfig(LumenIRTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  LumenIRTargetMachine &getTheLumenIRTargetMachine() const {
    return getTM<LumenIRTargetMachine>();
  }

  bool addInstSelector() override;
};
}

bool LumenIRPassConfig::addInstSelector() {
  addPass(createLumenIRISelDag(getTheLumenIRTargetMachine(), getOptLevel()));

  return false;
}


TargetPassConfig *LumenIRTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new LumenIRPassConfig(*this, PM);
}

