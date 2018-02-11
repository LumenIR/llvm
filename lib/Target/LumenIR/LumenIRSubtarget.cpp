//===-- LumenIRSubtarget.cpp - LumenIR Subtarget Information ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the LumenIR specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "LumenIRSubtarget.h"

#include "llvm/BinaryFormat/ELF.h"
#include "llvm/Support/TargetRegistry.h"

#include "LumenIR.h"
#include "LumenIRTargetMachine.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#define DEBUG_TYPE "lumenir-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LumenIRGenSubtargetInfo.inc"

namespace llvm {

LumenIRSubtarget::LumenIRSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, LumenIRTargetMachine &TM)
    : LumenIRGenSubtargetInfo(TT, CPU, FS), InstrInfo(), FrameLowering(),
      TLInfo(TM), TSInfo() {
  ParseSubtargetFeatures(CPU, FS);
}

} // end of namespace llvm
