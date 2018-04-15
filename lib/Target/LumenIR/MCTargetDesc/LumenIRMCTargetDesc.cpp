//===-- LumenIRMCTargetDesc.cpp - LumenIR Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// This file provides LumenIR-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "LumenIRMCAsmInfo.h"
#include "LumenIRMCTargetDesc.h"
#include "LumenIRELFStreamer.h"
#include "LumenIRTargetStreamer.h"
#include "InstPrinter/LumenIRInstPrinter.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "LumenIRGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "LumenIRGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "LumenIRGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createLumenIRMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitLumenIRMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createLumenIRMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  //TODO why 0?
  InitLumenIRMCRegisterInfo(X, 0);
  return X;
}

static MCAsmInfo *createLumenIRMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT) {
  return new LumenIRMCAsmInfo(TT);
}

static MCInstPrinter *createLumenIRMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new LumenIRInstPrinter(MAI, MII, MRI);
}

static MCSubtargetInfo *createLumenIRMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createLumenIRMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCTargetStreamer *createMCAsmTargetStreamer(MCStreamer &S,
                                                   formatted_raw_ostream &OS,
                                                   MCInstPrinter *InstPrint,
                                                   bool isVerboseAsm) {
  return new LumenIRTargetAsmStreamer(S);
}


static MCTargetStreamer *createLumenIRObjectTargetStreamer(MCStreamer &S,
                                                           const MCSubtargetInfo &STI) {
  return new LumenIRELFStreamer(S, STI);
}

static MCStreamer *createMCStreamer(const Triple &T, MCContext &Context,
                                    MCAsmBackend &MAB, raw_pwrite_stream &OS,
                                    MCCodeEmitter *Emitter, bool RelaxAll) {
  return createELFStreamer(Context, MAB, OS, Emitter, RelaxAll);
}

extern "C" void LLVMInitializeLumenIRTargetMC() {
  Target &T  = getTheLumenIRTarget();

  // Register the MC asm info.
  TargetRegistry::RegisterMCAsmInfo(T, createLumenIRMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(T, createLumenIRMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(T, createLumenIRMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(T, createLumenIRMCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(T, createLumenIRMCInstPrinter);

  // Register the asm backend
  TargetRegistry::RegisterMCAsmBackend(T, createLumenIRAsmBackend);

  // Register the MC Code Emitter
  TargetRegistry::RegisterMCCodeEmitter(T, createLumenIRMCCodeEmitter);


  // Register the ELF streamer TODO
  TargetRegistry::RegisterELFStreamer(T, createMCStreamer);

  // Register the obj target streamer TODO
  TargetRegistry::RegisterObjectTargetStreamer(T, createLumenIRObjectTargetStreamer);

  // Register the asm target streamer TODO
  TargetRegistry::RegisterAsmTargetStreamer(T, createMCAsmTargetStreamer);
}

