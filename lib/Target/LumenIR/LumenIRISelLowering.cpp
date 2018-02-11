//===-- LumenIRISelLowering.cpp - LumenIR DAG Lowering Implementation -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that LumenIR uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "LumenIRISelLowering.h"

#include "LumenIRTargetMachine.h"
#include "LumenIRRegisterInfo.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/ADT/StringSwitch.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"


namespace llvm {

LumenIRTargetLowering::LumenIRTargetLowering(LumenIRTargetMachine &tm)
    : TargetLowering(tm) {
  // Set up the register classes.
  addRegisterClass(MVT::i32, &LumenIR::sGPRRegClass);
  addRegisterClass(MVT::i64, &LumenIR::dGPRRegClass);

  addRegisterClass(MVT::f32, &LumenIR::sGPRRegClass);
  addRegisterClass(MVT::f64, &LumenIR::dGPRRegClass);

  setBooleanContents(ZeroOrOneBooleanContent);
  setBooleanVectorContents(ZeroOrOneBooleanContent);
  setSchedulingPreference(Sched::RegPressure);
  setStackPointerRegisterToSaveRestore(LumenIR::SP);
}




const char *LumenIRTargetLowering::getTargetNodeName(unsigned Opcode) const {
#define NODE(name)       \
  case LumenIRISD::name:     \
    return #name

  switch (Opcode) {
  default:
    return nullptr;
#undef NODE
  }
}


} // end of namespace llvm
