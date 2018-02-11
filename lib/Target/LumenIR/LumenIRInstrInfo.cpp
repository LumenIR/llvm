//===-- LumenIRInstrInfo.cpp - LumenIR Instruction Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LumenIR implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "LumenIRInstrInfo.h"

#include "LumenIR.h"
#include "LumenIRRegisterInfo.h"
#include "LumenIRSubtarget.h"
#include "LumenIRTargetMachine.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"


#define GET_INSTRINFO_CTOR_DTOR
#include "LumenIRGenInstrInfo.inc"


using namespace llvm;

LumenIRInstrInfo::LumenIRInstrInfo()
    : LumenIRGenInstrInfo(LumenIR::ADJCALLSTACKDOWN, LumenIR::ADJCALLSTACKUP), RI() {}

void LumenIRInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                               MachineBasicBlock::iterator MI,
                               const DebugLoc &DL, unsigned DestReg,
                               unsigned SrcReg, bool KillSrc) const {
  const LumenIRSubtarget &STI = MBB.getParent()->getSubtarget<LumenIRSubtarget>();
  const LumenIRRegisterInfo &TRI = *STI.getRegisterInfo();
  unsigned Opc;

  llvm_unreachable("Not implemented");

}



void LumenIRInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                       MachineBasicBlock::iterator MI,
                                       unsigned SrcReg, bool isKill,
                                       int FrameIndex,
                                       const TargetRegisterClass *RC,
                                       const TargetRegisterInfo *TRI) const {
  llvm_unreachable("Not implemented");

}

void LumenIRInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        unsigned DestReg, int FrameIndex,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI) const {
  llvm_unreachable("Not implemented");

}



bool LumenIRInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                 MachineBasicBlock *&TBB,
                                 MachineBasicBlock *&FBB,
                                 SmallVectorImpl<MachineOperand> &Cond,
                                 bool AllowModify) const {
    return false;
    //llvm_unreachable("Not implemented");
}

unsigned LumenIRInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                    MachineBasicBlock *TBB,
                                    MachineBasicBlock *FBB,
                                    ArrayRef<MachineOperand> Cond,
                                    const DebugLoc &DL,
                                    int *BytesAdded) const {
  return false;
}

unsigned LumenIRInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                    int *BytesRemoved) const {
  llvm_unreachable("Not implemented");
  return 0;
}

bool LumenIRInstrInfo::reverseBranchCondition(
    SmallVectorImpl<MachineOperand> &Cond) const {
  llvm_unreachable("Not implemented");

  return false;
}

unsigned LumenIRInstrInfo::getInstSizeInBytes(const MachineInstr &MI) const {

  llvm_unreachable("Not implemented");

  return 2;
}

MachineBasicBlock *
LumenIRInstrInfo::getBranchDestBlock(const MachineInstr &MI) const {
  llvm_unreachable("Not implemented");

  return nullptr;
}


