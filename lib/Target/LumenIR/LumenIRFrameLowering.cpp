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
  //TODO do we need prologue?
  //llvm_unreachable("Not implemented");
}

void LumenIRFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
 //TODO do we need epilogue?
 //llvm_unreachable("Not implemented");
}


bool LumenIRFrameLowering::spillCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    const std::vector<CalleeSavedInfo> &CSI,
    const TargetRegisterInfo *TRI) const {


  if (CSI.empty()) {
    return false;
  }

  DebugLoc DL = MBB.findDebugLoc(MI);
  unsigned CaleeSavedSize = 0;
  MachineFunction &MF = *MBB.getParent();
  const LumenIRSubtarget &STI = MF.getSubtarget<LumenIRSubtarget>();
  const TargetInstrInfo &TII = *STI.getInstrInfo();

  for (size_t i = CSI.size(); i !=0; --i) {
    unsigned Reg = CSI[i - 1].getReg();
    bool IsNotLiveIn = !MBB.isLiveIn(Reg);


    if(IsNotLiveIn) {
      MBB.addLiveIn(Reg);
    }

    unsigned Opc = 0;

    const TargetRegisterClass &RC = *TRI->getRegClass(Reg);

    switch (RC.getID()) {
    case LumenIR::GPRi8RegClassID:
      Opc = LumenIR::PushToStackRRi8;
      break;
    case LumenIR::GPRi16RegClassID:
      Opc = LumenIR::PushToStackRRi16;
      break;
    case LumenIR::GPRi32RegClassID:
      Opc = LumenIR::PushToStackRRi32;
      break;
    case LumenIR::GPRi64RegClassID:
      Opc = LumenIR::PushToStackRRi64;
      break;
    }

    BuildMI(MBB, MI, DL, TII.get(Opc))
            .addReg(Reg, getKillRegState(IsNotLiveIn));

  }


  return true;
}

bool LumenIRFrameLowering::restoreCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    const std::vector<CalleeSavedInfo> &CSI,
    const TargetRegisterInfo *TRI) const {

  if(CSI.empty()) {
    return false;
  }
  DebugLoc DL = MBB.findDebugLoc(MI);
  MachineFunction &MF = *MBB.getParent();
  const LumenIRSubtarget &STI = MF.getSubtarget<LumenIRSubtarget>();
  const TargetInstrInfo &TII = *STI.getInstrInfo();

  for (size_t i = 0, e = CSI.size(); i != e; ++i) {
      unsigned Reg = CSI[i].getReg();

      unsigned Opc = 0;
      const TargetRegisterClass &RC = *TRI->getRegClass(Reg);

      switch (RC.getID()) {
      case LumenIR::GPRi8RegClassID:
        Opc = LumenIR::PopFromStack8;
        break;
      case LumenIR::GPRi16RegClassID:
        Opc = LumenIR::PopFromStack16;
        break;
      case LumenIR::GPRi32RegClassID:
        Opc = LumenIR::PopFromStack32;
        break;
      case LumenIR::GPRi64RegClassID:
        Opc = LumenIR::PopFromStack64;
        break;
      }

      BuildMI(MBB, MI, DL, TII.get(Opc), Reg);
  }

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
  //TODO do we need to do smth?
  //  llvm_unreachable("Not implemented");
}

} // end of namespace llvm

