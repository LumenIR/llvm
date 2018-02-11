//===-- LumenIRRegisterInfo.cpp - LumenIR Register Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LumenIR implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "LumenIRRegisterInfo.h"

#include "LumenIR.h"
#include "LumenIRFrameLowering.h"
#include "LumenIRInstrInfo.h"
#include "LumenIRTargetMachine.h"

#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "LumenIRGenRegisterInfo.inc"

using namespace llvm;

LumenIRRegisterInfo::LumenIRRegisterInfo() : LumenIRGenRegisterInfo(0) {}

const uint16_t *
LumenIRRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  llvm_unreachable("Not implemented");

  return nullptr;
}

const uint32_t *
LumenIRRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  llvm_unreachable("Not implemented");

  return nullptr;
}

BitVector LumenIRRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  llvm_unreachable("Not implemented");
  return Reserved;
}

const TargetRegisterClass *
LumenIRRegisterInfo::getLargestLegalSuperClass(const TargetRegisterClass *RC,
                                               const MachineFunction &MF) const {

  llvm_unreachable("Not implemented");
}



void LumenIRRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
   llvm_unreachable("Not implemented");
}


unsigned LumenIRRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  llvm_unreachable("Not implemented");
}

const TargetRegisterClass *
LumenIRRegisterInfo::getPointerRegClass(const MachineFunction &MF,
                                    unsigned Kind) const {
  llvm_unreachable("Not implemented");
}

