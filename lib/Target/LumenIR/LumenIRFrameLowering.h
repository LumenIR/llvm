//===-- LumenIRFrameLowering.h - Define frame lowering for LumenIR ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_FRAME_LOWERING_H
#define LLVM_LUMENIR_FRAME_LOWERING_H

#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {

/// Utilities for creating function call frames.
class LumenIRFrameLowering : public TargetFrameLowering {
public:
  explicit LumenIRFrameLowering();

public:
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;


  bool spillCalleeSavedRegisters(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator MI,
                                 const std::vector<CalleeSavedInfo> &CSI,
                                 const TargetRegisterInfo *TRI) const override;

  bool hasFP(const MachineFunction &MF) const override { return true; }

  bool restoreCalleeSavedRegisters(MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator MI,
                              const std::vector<CalleeSavedInfo> &CSI,
                              const TargetRegisterInfo *TRI) const override;
  bool canSimplifyCallFramePseudos(const MachineFunction &MF) const override;
  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS = nullptr) const override;
  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI) const override;
};

} // end namespace llvm

#endif // LLVM_LUMENIR_FRAME_LOWERING_H
