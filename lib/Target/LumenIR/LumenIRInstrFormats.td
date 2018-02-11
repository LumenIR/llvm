//===-- LumenIRInstrInfo.td - LumenIR Instruction Formats ----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// LumenIR Instruction Format Definitions.
//
//===----------------------------------------------------------------------===//

// A generic LumenIR instruction.
class LumenIRInst<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction
{
  let Namespace = "LumenIR";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
}

/// A 16-bit LumenIR instruction. only RR instructions
class LumenIRInst16<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  field bits<16> Inst;
  let Inst{15-14} = 0b00;

  let Size = 2;
}

///  size| Opcode              | rh1 |
/// | 0 0|0 0 0 c c c c c c c c|d d d|
class LumenIRInst16R<bits<8> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst16<outs, ins, asmstr, pattern>
{
  bits<3> rh1;

  let Inst{13} = 0b0;
  let Inst{12} = 0b0;
  let Inst{11} = 0b0;

  let Inst{10-3} = opcode;
  let Inst{2-0}  = rh1;
}

///  size| Opcode    |          Imm8 |
/// | 0 0|0 0 1 c c c|i i i i i i i i|
class LumenIRInst16I<bits<3> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst16<outs, ins, asmstr, pattern>
{
  bits<8> rh1i;

  let Inst{13} = 0b0;
  let Inst{12} = 0b0;
  let Inst{11} = 0b1;

  let Inst{10-8} = opcode;
  let Inst{7-0}  = rh1i;
}

///  size| Opcode                    |
/// | 0 0|0 1 c c c c c c c c c c c c|
class LumenIRInst16Spec<bits<12> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst16<outs, ins, asmstr, pattern>
{
  let Inst{13} = 0b0;
  let Inst{12} = 0b1;

  let Inst{11-0} = opcode;
}

/// |size| Opcode  | lh  | rh1 | rh2 |
/// | 0 0|1 c c c c|d d d|x x x|y y y|
class LumenIRInst16RR<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst16<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<3> rh2;

  let Inst{13} = 0b1;
  let Inst{12-9} = opcode;

  let Inst{8-6} = lh;
  let Inst{5-3} = rh1;
  let Inst{2-0} = rh2;
}


/// a 32-bit LumenIR instruction. RR and RI16 instructions
class LumenIRInst32<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  field bits<32> Inst;
  let Inst{31-30} = 0b01;

  let Size = 4;
}

/// |size|   Opcode{20}                             | lh  | rh1 | rh2 |
/// | 0 1| 1 c c c c c c c c c c c c c c c c c c c c|d d d|x x x|y y y|
class LumenIRInst32RR<bits<20> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst32<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<3> rh2;

  let Inst{29} = 0b1;
  let Inst{28-9} = opcode;
  let Inst{8-6} = lh;
  let Inst{5-3} = rh1;
  let Inst{2-0} = rh2;
}

/// |size|   Opcode{7}    | lh  | rh1 | Imm16                         |
/// | 0 1| 0 c c c c c c c|d d d|x x x|i i i i i i i i i i i i i i i i|
class LumenIRInst32RI16<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst32<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<16> rh2I;

  let Inst{29} = 0b0;
  let Inst{28-22} = opcode;

  let Inst{21-19} = lh;
  let Inst{18-16} = rh1;
  let Inst{15-0}  = rh2I;
}


/// a 64-bit LumenIR instruction. RI32 instructions
class LumenIRInst64<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  field bits<64> Inst;
  let Inst{63-62} = 0b10;

  let Size = 8;
}

/// |size|   Opcode{7}    | lh  | rh1 | Reserved 16 | Imm32 |
/// | 1 0| 0 c c c c c c c|d d d|x x x|0 0    ... 0 |i ... i|
class LumenIRInst64RI32<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst64<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<32> rh2I;

  let Inst{61} = 0b0;
  let Inst{60-54} = opcode;

  let Inst{53-51} = lh;
  let Inst{50-48} = rh1;
  let Inst{47-32} = 0b0000000000000000; // reserved
  let Inst{31-0}  = rh2I;
}


/// a 96-bit LumenIR instruction. RI64 instructions
class LumenIRInst96<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  field bits<96> Inst;
  let Inst{95-94} = 0b11;

  let Size = 12;
}

/// |size|   Opcode{7}    | lh  | rh1 | Reserved 16 | Imm64 |
/// | 1 1| 0 c c c c c c c|d d d|x x x|0 0    ... 0 |i ... i|
class LumenIRInst96RI64<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst96<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<64> rh2I;

  let Inst{93}    = 0b0;
  let Inst{92-86} = opcode;
  let Inst{85-83} = lh;
  let Inst{82-80} = rh1;
  let Inst{79-64} = 0b0000000000000000; // reserved
  let Inst{63-0}  = rh2I;
}



class PseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  let Pattern = pattern;

  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

