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

#define DEBUG_TYPE "lumenir-registerinfo"


using namespace llvm;

LumenIRRegisterInfo::LumenIRRegisterInfo() : LumenIRGenRegisterInfo(0) {}

const uint16_t *
LumenIRRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
//  llvm_unreachable("Not implemented");

  return CSR_SaveList;
}

const uint32_t *
LumenIRRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  llvm_unreachable("Not implemented");

  return nullptr;
}

BitVector LumenIRRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());


  // do we need to add special regs that is not mentioned in ISelLowering ?
  Reserved.set(LumenIR::SP);
  Reserved.set(LumenIR::FP);

  return Reserved;
}

const TargetRegisterClass *
LumenIRRegisterInfo::getLargestLegalSuperClass(const TargetRegisterClass *RC,
                                               const MachineFunction &MF) const {
  const TargetRegisterInfo *TRI = MF.getSubtarget().getRegisterInfo();

  if (TRI->isTypeLegalForClass(*RC, MVT::i8)) {
    return &LumenIR::GPRi8RegClass;
  }

  if (TRI->isTypeLegalForClass(*RC, MVT::i16)) {
    return &LumenIR::GPRi16RegClass;
  }

  if (TRI->isTypeLegalForClass(*RC, MVT::i32)) {
    return &LumenIR::GPRi32RegClass;
  }

  if (TRI->isTypeLegalForClass(*RC, MVT::i64)) {
    return &LumenIR::GPRi64RegClass;
  }

  if (TRI->isTypeLegalForClass(*RC, MVT::f32)) {
    return &LumenIR::GPRf32RegClass;
  }

  if (TRI->isTypeLegalForClass(*RC, MVT::f64)) {
    return &LumenIR::GPRf64RegClass;
  }
  llvm_unreachable("Invalid register size");
}



void LumenIRRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
   //llvm_unreachable("Not implemented");

  MachineInstr &MI = *II;

  unsigned Opc = MI.getOpcode();

  switch (Opc) {
  default:
  {
    DEBUG(
      dbgs() << "eliminateFrameIndex not implemented:";
      MI.dump();
      dbgs() << "\n";
    );
  }
  case LumenIR::StoreToStackVRI32:
  case LumenIR::StoreToStackVRR32:
  case LumenIR::LoadFromStack8:
  case LumenIR::LoadFromStack16:
  case LumenIR::LoadFromStack32:
//  case LumenIR::LoadFromStack64: TODO
  {
    MachineOperand &FIOperand = MI.getOperand(FIOperandNum);
    int FI = FIOperand.getIndex();

    FIOperand.ChangeToImmediate(FI);

    break;
  }
  }
}


unsigned LumenIRRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return LumenIR::FP;
}

unsigned LumenIRRegisterInfo::getStackRegister(const MachineFunction &MF) const {
  return LumenIR::SP;
}

const TargetRegisterClass *
LumenIRRegisterInfo::getPointerRegClass(const MachineFunction &MF,
                                    unsigned Kind) const {
  return &LumenIR::GPRi64RegClass;
}

