//===-- LumenIRMCTargetDesc.h - LumenIR Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides LumenIR specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LUMENIR_MCTARGETDESC_LUMENIRMCTARGETDESC_H
#define LLVM_LIB_TARGET_LUMENIR_MCTARGETDESC_LUMENIRMCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class StringRef;
class Target;
class Triple;
class raw_ostream;
class raw_pwrite_stream;

Target &getTheLumenIRTarget();

MCCodeEmitter *createLumenIRMCCodeEmitter(const MCInstrInfo &MCII,
                                        const MCRegisterInfo &MRI,
                                        MCContext &Ctx);

MCAsmBackend *createLumenIRAsmBackend(const Target &T, const MCRegisterInfo &MRI,
                                    const Triple &TT, StringRef CPU,
                                    const MCTargetOptions &Options);

MCObjectWriter *createLumenIRELFObjectWriter(raw_pwrite_stream &OS);

} // namespace llvm

// Defines symbolic names for LumenIR registers.
#define GET_REGINFO_ENUM
#include "LumenIRGenRegisterInfo.inc"

// Defines symbolic names for LumenIR instructions.
#define GET_INSTRINFO_ENUM
#include "LumenIRGenInstrInfo.inc"

#endif
