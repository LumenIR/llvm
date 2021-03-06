//===-- LumenIRSubtarget.h - Define Subtarget for the LumenIR -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the LumenIR specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_SUBTARGET_H
#define LLVM_LUMENIR_SUBTARGET_H

#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#include "LumenIRFrameLowering.h"
#include "LumenIRISelLowering.h"
#include "LumenIRInstrInfo.h"
#include "LumenIRSelectionDAGInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "LumenIRGenSubtargetInfo.inc"

namespace llvm {

/// A specific LumenIR subtarget
class LumenIRSubtarget : public LumenIRGenSubtargetInfo {
public:
  //! Creates an LumenIR subtarget.
  //! \param TT  The target triple.
  //! \param CPU The CPU to target.
  //! \param FS  The feature string.
  //! \param TM  The target machine.
  LumenIRSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               LumenIRTargetMachine &TM);

  const LumenIRInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TargetFrameLowering *getFrameLowering() const override { return &FrameLowering; }
  const LumenIRRegisterInfo *getRegisterInfo() const override { return &InstrInfo.getRegisterInfo(); }
  const LumenIRTargetLowering *getTargetLowering() const override { return &TLInfo; }

  /// Parses a subtarget feature string, setting appropriate options.
  /// \note Definition of function is auto generated by `tblgen`.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

private:
  LumenIRInstrInfo InstrInfo;
  LumenIRFrameLowering FrameLowering;
  LumenIRTargetLowering TLInfo;
  LumenIRSelectionDAGInfo TSInfo;

};

} // end namespace llvm

#endif // LLVM_LumenIR_SUBTARGET_H
