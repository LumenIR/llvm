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

//===----------------------------------------------------------------------===//
// LumenIR Type Profiles
//===----------------------------------------------------------------------===//

def SDT_LumenIRCallSeqStart : SDCallSeqStart<[SDTCisVT<0, i16>, SDTCisVT<1, i16>]>;
def SDT_LumenIRCallSeqEnd : SDCallSeqEnd<[SDTCisVT<0, i16>, SDTCisVT<1, i16>]>;

//def SDT_LumenIRCall : SDTypeProfile<0, -1, [SDTCisVT<0, iPTR>]>;


//===----------------------------------------------------------------------===//
// LumenIR Specific Node Definitions
//===----------------------------------------------------------------------===//

def LumenIRcallseq_start : SDNode<"ISD::CALLSEQ_START", SDT_LumenIRCallSeqStart,
                              [SDNPHasChain, SDNPOutGlue]>;
def LumenIRcallseq_end : SDNode<"ISD::CALLSEQ_END", SDT_LumenIRCallSeqEnd,
                            [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;


// Basic instructions
//1
def IADD_RR32 : LumenIRInst16RR<0b0000, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "IADD $lhs, $rhs1, $rhs2", [(set i32:$lhs, (add i32:$rhs1, i32:$rhs2))]>;

//2
def SUBI_RR32 : LumenIRInst16RR<0b0001, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "ISUB $lhs, $rhs1, $rhs2", [(set i32:$lhs, (sub i32:$rhs1, i32:$rhs2))]>;

//3
def IMUL_RR32 : LumenIRInst16RR<0b0010, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "IMUL $lhs, $rhs1, $rhs2", [(set i32:$lhs, (mul i32:$rhs1, i32:$rhs2))]>;

//4
def AND_RR32 : LumenIRInst16RR<0b0011, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "AND $lhs, $rhs1, $rhs2", [(set i32:$lhs, (and i32:$rhs1, i32:$rhs2))]>;

//6
def OR_RR32 : LumenIRInst16RR<0b0100, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "OR $lhs, $rhs1, $rhs2", [(set i32:$lhs, (or i32:$rhs1, i32:$rhs2))]>;

//7
def XOR_RR32 : LumenIRInst16RR<0b0101, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "XOR $lhs, $rhs1, $rhs2", [(set i32:$lhs, (xor i32:$rhs1, i32:$rhs2))]>;

//8
def SRL_RR32 : LumenIRInst16RR<0b0110, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "SHIFTRL $lhs, $rhs1, $rhs2", [(set i32:$lhs, (srl i32:$rhs1, i32:$rhs2))]>;

//9
def SRA_RR32 : LumenIRInst16RR<0b0111, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "SHIFTRA $lhs, $rhs1, $rhs2", [(set i32:$lhs, (sra i32:$rhs1, i32:$rhs2))]>;

//10
def SHL_RR32 : LumenIRInst16RR<0b1000, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "SHIFTL $lhs, $rhs1, $rhs2", [(set i32:$lhs, (shl i32:$rhs1, i32:$rhs2))]>;

//11
def ROTL_RR32 : LumenIRInst16RR<0b1001, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "ROTL $lhs, $rhs1, $rhs2", [(set i32:$lhs, (rotl i32:$rhs1, i32:$rhs2))]>;

//12
def ROTR_RR32 : LumenIRInst16RR<0b1010, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "ROTR $lhs, $rhs1, $rhs2", [(set i32:$lhs, (rotr i32:$rhs1, i32:$rhs2))]>;

//13
def FADD_RR32 : LumenIRInst16RR<0b1011, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "FADD $lhs, $rhs1, $rhs2", [(set f32:$lhs, (fadd f32:$rhs1, f32:$rhs2))]>;

//14
def FSUB_RR32 : LumenIRInst16RR<0b1100, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "FSUB $lhs, $rhs1, $rhs2", [(set f32:$lhs, (fsub f32:$rhs1, f32:$rhs2))]>;

//15
def FMUL_RR32 : LumenIRInst16RR<0b1101, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "FMUL $lhs, $rhs1, $rhs2", [(set f32:$lhs, (fmul f32:$rhs1, f32:$rhs2))]>;

//16
def FDIV_RR32 : LumenIRInst16RR<0b1111, (outs sGPR:$lhs), (ins sGPR:$rhs1, sGPR:$rhs2),
  "FDIV $lhs, $rhs1, $rhs2", [(set f32:$lhs, (fdiv f32:$rhs1, f32:$rhs2))]>;



let Defs = [SP], Uses = [SP] in
{
  def ADJCALLSTACKDOWN : PseudoInst<(outs),
                                (ins i16imm:$amt, i16imm:$amt2),
                                "#ADJCALLSTACKDOWN",
                                [(LumenIRcallseq_start timm:$amt, timm:$amt2)]>;

  def ADJCALLSTACKUP : PseudoInst<(outs),
                              (ins i16imm:$amt1, i16imm:$amt2),
                              "#ADJCALLSTACKUP",
                              [(LumenIRcallseq_end timm:$amt1, timm:$amt2)]>;
}

