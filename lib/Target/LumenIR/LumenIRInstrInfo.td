//===-- LumenIRInstrInfo.td - Target Description for LumenIR ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the LumenIR instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "LumenIRInstrFormats.td"

def imm8 : PatLeaf<(imm), [{ return isUInt<8>(N->getZExtValue()); }]>;
def imm16 : PatLeaf<(imm), [{ return isUInt<16>(N->getZExtValue()); }]>;
def imm32 : PatLeaf<(imm), [{ return isUInt<32>(N->getZExtValue()); }]>;
def imm64 : PatLeaf<(imm), [{ return isUInt<64>(N->getZExtValue()); }]>;

def relbrtarget_8  : Operand<OtherVT>
{
  let PrintMethod = "printPCRelImm";
  let EncoderMethod = "encodeRelCondBrTarget<LumenIR::fixup_8_pcrel>";
}

def relbrtargrt_16 : Operand<OtherVT>
{
  let PrintMethod = "printPCRelImm";
  let EncoderMethod = "encodeRelCondBrTarget<LumenIR::fixup_16_pcrel>";
}


//def AddrFI : ComplexPattern<i16, 1, "SelectAddrFI", [frameindex], []>;

//===----------------------------------------------------------------------===//
// LumenIR Type Profiles
//===----------------------------------------------------------------------===//

def SDT_LumenIRCallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;
def SDT_LumenIRCallSeqEnd : SDCallSeqEnd<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;

def SDT_LumenIRRet  : SDTypeProfile<0, -1, []>;
def SDT_LumenIRCall : SDTypeProfile<0, -1, [SDTCisVT<0, iPTR>]>;


//===----------------------------------------------------------------------===//
// LumenIR Specific Node Definitions
//===----------------------------------------------------------------------===//

def LumenIRcallseq_start : SDNode<"ISD::CALLSEQ_START", SDT_LumenIRCallSeqStart,
                              [SDNPHasChain,
                               SDNPOutGlue]>;

def LumenIRcallseq_end : SDNode<"ISD::CALLSEQ_END", SDT_LumenIRCallSeqEnd,
                            [SDNPHasChain,
                             SDNPOptInGlue,
                             SDNPOutGlue]>;

def LumenIRreturn : SDNode<"LumenIRISD::RETURN", SDT_LumenIRRet,
                           [SDNPHasChain,
                            SDNPOptInGlue,
                            SDNPVariadic]>;

def LumenIRcall   : SDNode<"LumenIRISD::CALL", SDT_LumenIRCall,
                           [SDNPHasChain,
                            SDNPOptInGlue,
                            SDNPOutGlue,
                            SDNPVariadic]>;

// Basic instructions


defm IADD : InstRRRScalarInt<1 , add, "IADD">;
defm ISUB : InstRRRScalarInt<2 , sub, "ISUB">;
defm IMUL : InstRRRScalarInt<3 , mul, "IMUL">;

defm OR   : InstRRRScalarInt<4 , or , "OR">;
defm XOR  : InstRRRScalarInt<5 , xor, "XOR">;

defm SRL  : InstRRRScalarInt<6 , srl,  "SRL">;
defm SRA  : InstRRRScalarInt<7 , sra,  "SRA">;
defm SHL  : InstRRRScalarInt<8 , shl,  "SHL">;
defm ROTL : InstRRRScalarInt<9 , rotl, "ROTL">;
defm ROTR : InstRRRScalarInt<10, rotr, "ROTR">;

defm FADD : InstRRRScalarFloat<11, fadd, "FADD">;
defm FSUB : InstRRRScalarFloat<12, fsub, "FSUB">;
defm FMUL : InstRRRScalarFloat<13, fmul, "FMUL">;
defm FDIV : InstRRRScalarFloat<14, fdiv, "FDIV">;



let Defs = [SP], Uses = [SP] in
{
  def ADJCALLSTACKDOWN : PseudoInst<(outs),
                                (ins i32imm:$amt, i32imm:$amt2),
                                "#ADJCALLSTACKDOWN",
                                [(LumenIRcallseq_start timm:$amt, timm:$amt2)]>;

  def ADJCALLSTACKUP : PseudoInst<(outs),
                              (ins i32imm:$amt1, i32imm:$amt2),
                              "#ADJCALLSTACKUP",
                              [(LumenIRcallseq_end timm:$amt1, timm:$amt2)]>;
}
//===----------------------------------------------------------------------===//
// Load/Store instructions
//===----------------------------------------------------------------------===//


let
  mayStore   = 1,
  Uses = [SP]
in {

  def StoreToStackVRI32 :
   InstVIVi32
   <T32.Coding,
    17,
    (outs),
    (ins i32imm:$rhs2I, GPRi32:$rhs1),
    "stack[$rhs2I] = $rhs1",
    []
   >;

  def StoreToStackVRR32 :
   InstVIVi32
   <T32.Coding,
    20,
    (outs),
    (ins GPRi32:$rhs2, GPRi32:$rhs1),
    "stack[$rhs2] = $rhs1",
    []
   >;

}

let
  mayStore = 1
in {
  defm StoreR :
    InstVRVInt<16, "void = store($rhs1)">;
}

let
  mayStore   = 1,
  Defs = [FP],
  Uses = [FP]
in {

  defm PushToStack :
    InstVRVInt<15, "void = push($rhs1)">;

}



let
  mayLoad   = 1,
  Defs      = [FP],
  Uses      = [FP]
in {

  defm PopFromStack :
    InstRVVInt<16, "$lhs = pop()">;
}

let
  mayLoad   = 1,
  Uses      = [SP]
in {

  defm LoadFromStack :
    InstRIVInt<17, "$lhs = stack[$rhs1]">;

  defm LoadFromStack :
    InstRRVInt<17, "$lhs = stack[$rhs1]">;
}

let
  mayLoad   = 1
in {

  def Load8 :
    InstRIV32<
      T8.Coding,
      21,
      (outs GPRi8:$lhs),
      (ins i32imm:$rhs1),
      "$lhs = load($rhs1)",
      []
//      [(set i8:$lhs, (load tglobaladdr:$rhs1))]
    >;


  def Load16 :
    InstRIV32<
      T16.Coding,
      21,
      (outs GPRi16:$lhs),
      (ins i32imm:$rhs1),
      "$lhs = load($rhs1)",
      []
//       [(set i16:$lhs, (load tglobaladdr:$rhs1))]
    >;

  def Load32 :
    InstRIV32<
      T32.Coding,
      21,
      (outs GPRi32:$lhs),
      (ins i32imm:$rhs1),
      "$lhs = load($rhs1)",
      []
//      [(set i32:$lhs, (load tglobaladdr:$rhs1))]
    >;
//  defm LoadWithOffset
}

//===----------------------------------------------------------------------===//
// Imm to reg instructions
//===----------------------------------------------------------------------===//


def LoadData :
  InstRIV32<T32.Coding, 16,
   (outs GPRi32:$lhs),
   (ins i32imm:$rhs1),
   "$lhs = data($rhs1)",
   []
  >;

//===----------------------------------------------------------------------===//
// Return instructions.
//===----------------------------------------------------------------------===//



let
  isTerminator = 1,
  isReturn     = 1,
  isBarrier    = 1,
  Defs         = [RV,SP,FP],
  Uses         = [SP,FP]
in {
  def ReturnVoid : InstVVV<19,
                (outs),
                (ins),
                "void = return()",
                []>;
}

let
  isTerminator = 1,
  isReturn     = 1,
  isBarrier    = 1,
  Defs         = [RV,SP,FP],
  Uses         = [SP,FP]
in {
  def Return : InstVRV<T32.Coding,
                18,
                (outs),
                (ins GPRi32:$rhs1),
                "void = return($rhs1)",
                [(LumenIRreturn T32.Type:$rhs1)]>;

}

//===----------------------------------------------------------------------===//
// PTR instructions
//===----------------------------------------------------------------------===//

let
  Uses = [SP]
in {
  def GetPtrFromFI : InstRRV<T64.Coding,
                           0,
                           (outs GPRi64:$lhs),
                           (ins GPRi64:$rhs1),
                           "$lhs = ptrFromFI($rhs1)",
                           []>;
}



