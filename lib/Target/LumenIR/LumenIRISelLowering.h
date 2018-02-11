//===-- LumenIRISelLowering.h - LumenIR DAG Lowering Interface ----------*- C++ -*-===//
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

#ifndef LLVM_LUMENIR_ISEL_LOWERING_H
#define LLVM_LUMENIR_ISEL_LOWERING_H

#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {

namespace LumenIRISD {

/// LumenIR Specific DAG Nodes
enum NodeType {
  /// Start the numbering where the builtin ops leave off.
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
};

} // end of namespace LumenIRISD

class LumenIRTargetMachine;

/// Performs target lowering for the LumenIR.
class LumenIRTargetLowering : public TargetLowering {
public:
  explicit LumenIRTargetLowering(LumenIRTargetMachine &TM);

public:
  MVT getScalarShiftAmountTy(const DataLayout &, EVT LHSTy) const override {
    return MVT::i8;
  }

  MVT::SimpleValueType getCmpLibcallReturnType() const override {
    return MVT::i8;
  }

  const char *getTargetNodeName(unsigned Opcode) const override;

//  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

//  void ReplaceNodeResults(SDNode *N, SmallVectorImpl<SDValue> &Results,
//                          SelectionDAG &DAG) const override;

//  bool isLegalAddressingMode(const DataLayout &DL, const AddrMode &AM, Type *Ty,
//                             unsigned AS) const override;

//  bool getPreIndexedAddressParts(SDNode *N, SDValue &Base, SDValue &Offset,
//                                 ISD::MemIndexedMode &AM,
//                                 SelectionDAG &DAG) const override;

//  bool getPostIndexedAddressParts(SDNode *N, SDNode *Op, SDValue &Base,
//                                  SDValue &Offset, ISD::MemIndexedMode &AM,
//                                  SelectionDAG &DAG) const override;

//  bool isOffsetFoldingLegal(const GlobalAddressSDNode *GA) const override;

//  EVT getSetCCResultType(const DataLayout &DL, LLVMContext &Context,
//                         EVT VT) const override;

//  MachineBasicBlock *
//  EmitInstrWithCustomInserter(MachineInstr &MI,
//                              MachineBasicBlock *MBB) const override;

//  ConstraintType getConstraintType(StringRef Constraint) const override;

//  ConstraintWeight
//  getSingleConstraintMatchWeight(AsmOperandInfo &info,
//                                 const char *constraint) const override;

//  std::pair<unsigned, const TargetRegisterClass *>
//  getRegForInlineAsmConstraint(const TargetRegisterInfo *TRI,
//                               StringRef Constraint, MVT VT) const override;

 // unsigned getInlineAsmMemConstraint(StringRef ConstraintCode) const override;

//  void LowerAsmOperandForConstraint(SDValue Op, std::string &Constraint,
//                                    std::vector<SDValue> &Ops,
//                                    SelectionDAG &DAG) const override;

//  unsigned getRegisterByName(const char* RegName, EVT VT,
//                             SelectionDAG &DAG) const override;

private:


//  bool CanLowerReturn(CallingConv::ID CallConv,
//                      MachineFunction &MF, bool isVarArg,
//                      const SmallVectorImpl<ISD::OutputArg> &Outs,
//                      LLVMContext &Context) const override;

//  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
//                      const SmallVectorImpl<ISD::OutputArg> &Outs,
//                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &dl,
//                      SelectionDAG &DAG) const override;
//  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
//                               bool isVarArg,
//                               const SmallVectorImpl<ISD::InputArg> &Ins,
//                               const SDLoc &dl, SelectionDAG &DAG,
//                               SmallVectorImpl<SDValue> &InVals) const override;
//  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
//                    SmallVectorImpl<SDValue> &InVals) const override;

};

} // end namespace llvm

#endif // LLVM_LumenIR_ISEL_LOWERING_H
