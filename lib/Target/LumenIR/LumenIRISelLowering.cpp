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
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"


namespace llvm {

static void fail(const SDLoc &DL, SelectionDAG &DAG, StringRef msg) {
  MachineFunction &MF = DAG.getMachineFunction();
  DAG.getContext()->diagnose(
      DiagnosticInfoUnsupported(*MF.getFunction(), msg, DL.getDebugLoc())
  );
}

LumenIRTargetLowering::LumenIRTargetLowering(LumenIRTargetMachine &tm)
    : TargetLowering(tm) {
  // Set up the register classes.
  addRegisterClass(MVT::i8 , &LumenIR::GPRi8RegClass);
  addRegisterClass(MVT::i16, &LumenIR::GPRi16RegClass);

  addRegisterClass(MVT::i32, &LumenIR::GPRi32RegClass);
  addRegisterClass(MVT::i64, &LumenIR::GPRi64RegClass);

  addRegisterClass(MVT::f32, &LumenIR::GPRf32RegClass);
  addRegisterClass(MVT::f64, &LumenIR::GPRf64RegClass);

  // computeRegisterProperties - Once all of the register classes are added,
  // this allows us to compute derived properties we expose.
  computeRegisterProperties(tm.getSubtargetImpl()->getRegisterInfo());

  setBooleanContents(ZeroOrOneBooleanContent);
  setBooleanVectorContents(ZeroOrOneBooleanContent);
  setSchedulingPreference(Sched::RegPressure);
  setStackPointerRegisterToSaveRestore(LumenIR::SP);
}
//===----------------------------------------------------------------------===//
//                     IR Instruction Lowering
//===----------------------------------------------------------------------===//

SDValue LumenIRTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  return Op;
}

//===----------------------------------------------------------------------===//
//             Calling Convention Implementation
//===----------------------------------------------------------------------===//


#include "LumenIRGenCallingConv.inc"


SDValue LumenIRTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv,
    bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins,
    const SDLoc &dl,
    SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const {

  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo &MFI = MF.getFrameInfo();


  SmallVector<CCValAssign, 16> ArgLocs;

  CCState CCInfo(CallConv, isVarArg, MF, ArgLocs, *DAG.getContext());

  CCInfo.AnalyzeFormalArguments(Ins, ArgCC_LumenIR);


  for (size_t i = 0, e = ArgLocs.size(); i < e; ++i) {
    CCValAssign &VA = ArgLocs[i];

    ISD::ArgFlagsTy Flags = Ins[i].Flags;

    assert(VA.isMemLoc() && "Only on stack parametres supported for now");
    unsigned ObjSize = 0;
    if (Flags.isByVal()) {
      ObjSize = Flags.getByValSize();
    } else {
      ObjSize = VA.getLocVT().getStoreSize();
    }
    unsigned StackLocation = VA.getLocMemOffset();
    int FI = MFI.CreateFixedObject(ObjSize, StackLocation, true);

    SDValue FINode = DAG.getFrameIndex(FI, MVT::i32);

    if (Flags.isByVal()) {
      InVals.push_back(FINode);
    } else {
      InVals.push_back(
                  DAG.getLoad(VA.getValVT(), dl, Chain, FINode, MachinePointerInfo())
      );
    }

  }

  if (isVarArg) {
    llvm_unreachable("VaArg is not supported");
  }

  return Chain;
}

bool LumenIRTargetLowering::CanLowerReturn(CallingConv::ID CallConv,
                             MachineFunction &MF, bool isVarArg,
                             const SmallVectorImpl<ISD::OutputArg> &Outs,
                             LLVMContext &Context) const {
  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, MF, RVLocs, Context);
  return CCInfo.CheckReturn(Outs, RetCC_LumenIR);
}

SDValue LumenIRTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                                           const SmallVectorImpl<ISD::OutputArg> &Outs,
                                           const SmallVectorImpl<SDValue> &OutVals, const SDLoc &dl,
                                           SelectionDAG &DAG) const {
  assert(Outs.size() <= 1 && "LumenIR cannot return > 1 elements");

  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), RVLocs, *DAG.getContext());

  CCInfo.AnalyzeReturn(Outs, RetCC_LumenIR);

//  SDValue Flag;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (size_t i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");
    assert(i < 1 && "Can only return one register!");

    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
    RetOps[0] = DAG.getCopyToReg(Chain, dl, VA.getLocReg(), OutVals[i]);
  }

  // Do we need glue here?
//  RetOps[0] = Chain;
//  if (Flag.getNode()) {
//      RetOps.push_back(Flag);
//  }
//  unsigned Opc = 0;
//  if (RetOps.size() > 1){
//      Opc = LumenIRISD::RETURN;
//  } else

  return DAG.getNode(LumenIRISD::RETURN, dl, MVT::Other, RetOps);
}


SDValue LumenIRTargetLowering::LowerCall(
        TargetLowering::CallLoweringInfo &CLI,
        SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG         = CLI.DAG;
  SDLoc DL                  = CLI.DL;
  SDValue Chain             = CLI.Chain;
  SDValue Callee            = CLI.Callee;
  CallingConv::ID CallConv  = CLI.CallConv;

  MachineFunction &MF       = DAG.getMachineFunction();
  MachineFrameInfo &MFI     = MF.getFrameInfo();
  auto &ST                  = MF.getSubtarget<LumenIRSubtarget>();
  auto &RI                  = *ST.getRegisterInfo();

  DataLayout Layout         = MF.getDataLayout();
  auto PtrVT                = getPointerTy(Layout);

  if(CLI.IsPatchPoint)
      fail(DL, DAG, "LumenIR doesn't support patch point");

  //TODO check opts and assert
  CLI.IsTailCall = false;

  // Check VarArgs
  unsigned NumNamedVarArgParams = -1U;
  if(GlobalAddressSDNode *GAN = dyn_cast<GlobalAddressSDNode>(Callee)) {
    const GlobalValue *GV = GAN->getGlobal();
    Callee = DAG.getTargetGlobalAddress(GV, DL, MVT::i32);
    if (const Function *F = dyn_cast<Function>(GV)) {
      if(F->isVarArg() && F->getFunctionType()->getNumParams() != 0) {
        NumNamedVarArgParams = F->getFunctionType()->getNumParams();
      }
    }
  }

  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, CLI.IsVarArg, MF, ArgLocs, *DAG.getContext());

  if(CLI.IsVarArg)
    llvm_unreachable("VarArg is not supported");
  else
    CCInfo.AnalyzeCallOperands(CLI.Outs, ArgCC_LumenIR);

  unsigned StackOffset = CCInfo.getNextStackOffset();
  SmallVector<SDValue, 16> MemOpChains;

  SDValue StackPtr = DAG.getCopyFromReg(Chain, DL, RI.getStackRegister(MF), PtrVT);

  for(size_t i = 0, e = ArgLocs.size(); i < e; ++i) {
    CCValAssign &VA         = ArgLocs[i];
    SDValue Arg             = CLI.OutVals[i];
    ISD::ArgFlagsTy Flags   = CLI.Outs[i].Flags;

    // Promote value if needed
    switch (VA.getLocInfo()) {
      default:
        llvm_unreachable("Unknown loc info");
      case CCValAssign::BCvt:
      case CCValAssign::Full:
        break;
      case CCValAssign::SExt:
        Arg = DAG.getNode(ISD::SIGN_EXTEND, DL, VA.getLocVT(), Arg);
        break;
      case CCValAssign::ZExt:
        Arg = DAG.getNode(ISD::ZERO_EXTEND, DL, VA.getLocVT(), Arg);
        break;
      case CCValAssign::AExt:
        Arg = DAG.getNode(ISD::ANY_EXTEND, DL, VA.getLocVT(), Arg);
        break;
    }

    if (VA.isMemLoc()) {
        unsigned LocMemOffset = VA.getLocMemOffset();
        SDValue MemAddr = DAG.getConstant(LocMemOffset, DL, StackPtr.getValueType());

        MemAddr = DAG.getNode(ISD::ADD, DL, MVT::i32, StackPtr, MemAddr);
        if (Flags.isByVal()) {
                    llvm_unreachable("By val params not supported");
          // Arg is struct passed by value -> Arg is a pointer

//TODO          MemOpChains.push_back()
        } else {
            MachinePointerInfo LocPI = MachinePointerInfo::getStack(
                        MF, LocMemOffset
            );
            MemOpChains.push_back(
                        DAG.getStore(Chain, DL, Arg, MemAddr, LocPI)
            );
        }
    } else {
        llvm_unreachable("Only stack params supported");
    }
  }
  if (!MemOpChains.empty()) {
      //Make all stores independent
      Chain = DAG.getNode(ISD::TokenFactor, DL, MVT::Other, MemOpChains);
  }

  SDValue Glue;
  Chain = DAG.getCALLSEQ_START(Chain, StackOffset, 0, DL);
  Glue = Chain.getValue(1);


  unsigned char Flags = 0; //TODO understand it
  // GlobalAddress/ExternalSymbol -> TargetGlobalAddress/TargetExternalSymbol
  if (auto *G = dyn_cast<GlobalAddressSDNode>(Callee)) {
    Callee = DAG.getTargetGlobalAddress(G->getGlobal(), DL, PtrVT, 0, Flags);
  } else if (auto *S = dyn_cast<ExternalSymbolSDNode>(Callee)) {
    Callee = DAG.getTargetExternalSymbol(S->getSymbol(), PtrVT, Flags);
  }

  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);
  SmallVector<SDValue, 16> Ops;
  Ops.push_back(Chain);
  Ops.push_back(Callee);

  const uint32_t *Mask = RI.getCallPreservedMask(MF, CallConv);
  assert(Mask && "Missing call preserved mask for calling convention");
  Ops.push_back(DAG.getRegisterMask(Mask));

  MFI.setHasCalls(true);

  Chain = DAG.getNode(LumenIRISD::CALL, DL, NodeTys, Ops);
  Glue = Chain.getValue(1);

  Chain = DAG.getCALLSEQ_END(
              Chain,
              DAG.getIntPtrConstant(StackOffset, DL, true),
              DAG.getIntPtrConstant(0, DL, true),
              Glue,
              DL
  );

  return LowerCallResult(CLI, Chain, Glue, Callee, InVals);

}

SDValue LumenIRTargetLowering::LowerCallResult(
        TargetLowering::CallLoweringInfo &CLI,
        SDValue Chain,
        SDValue Glue,
        SDValue Callee,
        SmallVectorImpl<SDValue> &InVals
        ) const {

  SmallVector<CCValAssign, 16> RVLocs;

  CCState CCInfo(
              CLI.CallConv,
              CLI.IsVarArg,
              CLI.DAG.getMachineFunction(),
              RVLocs,
              *CLI.DAG.getContext()
  );
  CCInfo.AnalyzeCallResult(CLI.Ins, RetCC_LumenIR);

  for (size_t i = 0, e = RVLocs.size(); i < e; ++i) {
      SDValue RetVal = CLI.DAG.getCopyFromReg(Chain, CLI.DL, RVLocs[i].getLocReg(), RVLocs[i].getValVT(), Glue);
      Glue = RetVal.getValue(2);
      InVals.push_back(RetVal.getValue(0));
      Chain = RetVal.getValue(1);
  }

  return Chain;
}


const char *LumenIRTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (static_cast<LumenIRISD::NodeType>(Opcode)) {
  default:
    return nullptr;

#define HANDLE_NODETYPE(NODE) \
  case LumenIRISD::NODE:     \
    return "LumenIRISD::" #NODE;
#include "LumenIRISD.def"

#undef HANDLE_NODETYPE
  }
}


} // end of namespace llvm
