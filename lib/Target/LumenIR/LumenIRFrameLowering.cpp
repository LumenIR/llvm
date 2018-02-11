//===-- LumenIRFrameLowering.cpp - LumenIR Frame Information ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LumenIR implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "LumenIRFrameLowering.h"

#include "LumenIR.h"
#include "LumenIRInstrInfo.h"
#include "LumenIRSubtarget.h"
#include "LumenIRTargetMachine.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Function.h"

#include <vector>

namespace llvm {

LumenIRFrameLowering::LumenIRFrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 1, -2) {}

bool LumenIRFrameLowering::canSimplifyCallFramePseudos(
    const MachineFunction &MF) const {
  // Always simplify call frame pseudo instructions, even when
  // hasReservedCallFrame is false.
  return true;
}


void LumenIRFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  llvm_unreachable("Not implemented");
}

void LumenIRFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  llvm_unreachable("Not implemented");
}


bool LumenIRFrameLowering::spillCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    const std::vector<CalleeSavedInfo> &CSI,
    const TargetRegisterInfo *TRI) const {

  llvm_unreachable("Not implemented");

  return true;
}

bool LumenIRFrameLowering::restoreCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    const std::vector<CalleeSavedInfo> &CSI,
    const TargetRegisterInfo *TRI) const {

  llvm_unreachable("Not implemented");

  return true;
}


MachineBasicBlock::iterator LumenIRFrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &MF, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator MI) const {
  const LumenIRSubtarget &STI = MF.getSubtarget<LumenIRSubtarget>();
  const TargetFrameLowering &TFI = *STI.getFrameLowering();
  const LumenIRInstrInfo &TII = *STI.getInstrInfo();

  llvm_unreachable("Not implemented");

  return MBB.erase(MI);
}

void LumenIRFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                            BitVector &SavedRegs,
                                            RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
  llvm_unreachable("Not implemented");
}

} // end of namespace llvm

