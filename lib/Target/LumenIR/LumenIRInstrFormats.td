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



// GPR - 128 bits with subregs


//  | 31 30 29 28|27 26 25 24|23 22 21 20 19 18 17 16 15 14 13 12 11 10  8  8  7  6  5  4  3  2  1  0|
//     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
/// |prefix      |     rs    |   lhs  |    rhs1|   rhs2 | Opcode                                     |
/// |  s  s  s  s| z  z  z  z| r  r  r| r  r  r| r  r  r| o  o  o  o  o  o  o  o  o  o  o  o  o  o  o|

/// prefix
// 0 0 0 0  lhs = f(rhs1, rhs2 ) //RRR
// 0 0 0 1  lhs = f(rhs1, rhs2I) //RRI  // rhs2I - immediate value encoded in next bytes after current instruction depending on rs (32-128 bits)

// 0 0 1 1 void = f(rhs1, rhs2 ) //VRR  // special instructions writing or reading special registers (e.g. PC,SP,FP)
// 0 1 0 1 void = f(rhs1, rhs2I) //VRI  // combination of previous 2 types
// 0 1 1 0  lhs = f(rhs1       ) //RRV
// 0 1 1 1  lhs = f(rhs1I      ) //RIV
// 1 0 0 0 void = f(rhs1       ) //VRV
// 1 0 0 1 void = f(rhs1I      ) //VIV
// 1 0 1 0  lhs = f(           ) //RVV
// 1 0 1 1 void = f(           ) //VVV

/// rs - register size
// 0 0 0 0 - bool   1 bit

// bits     size in  bits   asm suffix
// 0 0 0 1 - byte    8   bit   :8
// 0 0 1 0 - word    16  bit   :16
// 0 0 1 1 - single  32  bit   :32
// 0 1 0 0 - double  64  bit   :64
// 0 1 0 1 - quad    128 bit   :128
/// vectors

// 1 0 0 1 - 8 bytes           :8v8
// 1 0 1 0 - 4 words           :4v16
// 1 0 1 1 - 2 singles         :2v32
// 1 1 0 0 ...

//     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
/// | type       |     rs    |   lhs  |    rhs1|   rhs2 | Opcode                                     |
/// |  s  s  s  s| z  z  z  z| r  r  r| r  r  r| r  r  r| o  o  o  o  o  o  o  o  o  o  o  o  o  o  o|

class RegType<bits<4> coding, string suf, ValueType type>
{
  bits<4> Coding;
  string Suf;
  ValueType Type;

  let Coding = coding;
  let Suf = suf;
  let Type = type;
}

def T8  : RegType<0b0001, ":8" , i8>;
def T16 : RegType<0b0010, ":16", i16>;
def T32 : RegType<0b0011, ":32", i32>;
def T64 : RegType<0b0100, ":64", i64>;


class Inst<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction
{
  let Namespace = "LumenIR";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
}

class InstBase32<bits<4> ops_type, bits<4> ops_size, bits<15> opcode,
               dag outs, dag ins, string asmstr, list<dag> pattern>
  : Inst<outs, ins, asmstr, pattern>
{
  field bits<32> Inst;
  field bits<32> SoftFail = 0;

  let Inst{31-28} = ops_type;
  let Inst{27-24} = ops_size;
  let Inst{14-0}  = opcode;

  let Size = 4;
}

class InstBase64<bits<4> ops_type, bits<4> ops_size, bits<15> opcode,
                 dag outs, dag ins, string asmstr, list<dag> pattern>
  : Inst<outs, ins, asmstr, pattern>
{
  field bits<64> Inst;
  field bits<64> SoftFail = 0;

  let Inst{63-60} = ops_type;
  let Inst{59-56} = ops_size;
  let Inst{46-32} = opcode;

  let Size = 8;
}

class InstBase96<bits<4> ops_type, bits<4> ops_size, bits<15> opcode,
                 dag outs, dag ins, string asmstr, list<dag> pattern>
  : Inst<outs, ins, asmstr, pattern>
{
  field bits<96> Inst;
  field bits<96> SoftFail = 0;

  let Inst{95-92} = ops_type;
  let Inst{91-88} = ops_size;
  let Inst{78-64} = opcode;

  let Size = 12;
}

class InstRRR<bits<4> ops_size, bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b0000, ops_size, opcode,
             outs, ins, asmstr, pattern>
{
  bits<3> lhs;
  bits<3> rhs1;
  bits<3> rhs2;

  let Inst{10-8}  = lhs;
  let Inst{13-11} = rhs1;
  let Inst{16-14} = rhs2;
}

class InstVRR<bits<4> ops_size, bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b0011, ops_size, opcode,
             outs, ins, asmstr, pattern>
{
  bits<3> rhs1;
  bits<3> rhs2;

  let Inst{10-8}  = 0b000;
  let Inst{13-11} = rhs1;
  let Inst{16-14} = rhs2;
}

class InstRRV<bits<4> ops_size, bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b0110, ops_size, opcode,
             outs, ins, asmstr, pattern>
{
  bits<3> lhs;
  bits<3> rhs1;

  let Inst{10-8}  = lhs;
  let Inst{13-11} = rhs1;
  let Inst{16-14} = 0b000;
}

class InstRIV32<bits<4> ops_size, bits<15> opcode,
                 dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase64<0b0111, ops_size, opcode,
               outs, ins, asmstr, pattern>
{
  bits<3>  lhs;
  bits<32> rhs1I;

  let Inst{42-40} = lhs;
  let Inst{45-43} = 0b000;
  let Inst{48-46} = 0b000;
  let Inst{0-31}  = rhs1I;
}

class InstVIVi32<bits<4> ops_size, bits<15> opcode,
                 dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase64<0b1001, ops_size, opcode,
               outs, ins, asmstr, pattern>
{
  bits<32> rhs1I;

  let Inst{42-40} = 0b000;
  let Inst{45-43} = 0b000;
  let Inst{48-46} = 0b000;
  let Inst{0-31}  = rhs1I;
}

class InstVRV<bits<4> ops_size, bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b1000, ops_size, opcode,
               outs, ins, asmstr, pattern>
{
  bits<3> rhs1;

  let Inst{10-8}  = 0b000;
  let Inst{13-11} = rhs1;
  let Inst{16-14} = 0b000;
}

class InstRVV<bits<4> ops_size, bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b1010, ops_size, opcode,
               outs, ins, asmstr, pattern>
{
  bits<3> lhs;

  let Inst{10-8}  = lhs;
  let Inst{13-11} = 0b000;
  let Inst{16-14} = 0b000;
}

class InstVVV<bits<15> opcode,
              dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstBase32<0b1011, 0b0000, opcode,
               outs, ins, asmstr, pattern>
{
  let Inst{10-8}  = 0b000;
  let Inst{13-11} = 0b000;
  let Inst{16-14} = 0b000;
}


// multiclasses

multiclass InstRRRScalarInt<bits<15> opcode, SDNode operation, string name>
{
  def #NAME#RRi8 : InstRRR<T8.Coding, opcode,
    (outs GPRi8:$lhs),
    (ins GPRi8:$rhs1, GPRi8:$rhs2),
    !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
    [(set i8:$lhs, (operation i8:$rhs1, i8:$rhs2))]>;

  def #NAME#RRi16 : InstRRR<T16.Coding, opcode,
   (outs GPRi16:$lhs),
   (ins GPRi16:$rhs1, GPRi16:$rhs2),
   !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
   [(set i16:$lhs, (operation i16:$rhs1, i16:$rhs2))]>;

  def #NAME#RRi32 : InstRRR<T32.Coding, opcode,
   (outs GPRi32:$lhs),
   (ins GPRi32:$rhs1, GPRi32:$rhs2),
   !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
   [(set i32:$lhs, (operation i32:$rhs1, i32:$rhs2))]>;

  def #NAME#RRi64 : InstRRR<T64.Coding, opcode,
   (outs GPRi64:$lhs),
   (ins GPRi64:$rhs1, GPRi64:$rhs2),
   !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
   [(set i64:$lhs, (operation i64:$rhs1, i64:$rhs2))]>;
}

multiclass InstRRRScalarFloat<bits<15> opcode, SDNode operation, string name>
{
  def #NAME#f32 : InstRRR<T32.Coding, opcode,
   (outs GPRf32:$lhs),
   (ins GPRf32:$rhs1, GPRf32:$rhs2),
   !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
   [(set f32:$lhs, (operation f32:$rhs1, f32:$rhs2))]>;

  def #NAME#f64 : InstRRR<T64.Coding, opcode,
   (outs GPRf64:$lhs),
   (ins GPRi64:$rhs1, GPRi64:$rhs2),
   !strconcat("$lhs = ", name, "($rhs1, $rhs2)"),
   [(set f64:$lhs, (operation f64:$rhs1, f64:$rhs2))]>;
}


multiclass InstVRVInt<bits<15> opcode, string asmstr>
{
  def #NAME#RRi8 : InstVRV<T8.Coding, opcode,
    (outs),
    (ins GPRi8:$rhs1),
    asmstr,
    []>;

  def #NAME#RRi16 : InstVRV<T16.Coding, opcode,
   (outs),
   (ins GPRi16:$rhs1),
   asmstr,
   []>;

  def #NAME#RRi32 : InstVRV<T32.Coding, opcode,
   (outs),
   (ins GPRi32:$rhs1),
   asmstr,
   []>;

  def #NAME#RRi64 : InstVRV<T64.Coding, opcode,
   (outs),
   (ins GPRi64:$rhs1),
   asmstr,
   []>;
}

multiclass InstRRVInt<bits<15> opcode, string asmstr>
{
  def #NAME#RRi8 : InstVRV<T8.Coding, opcode,
    (outs GPRi8:$lhs),
    (ins GPRi8:$rhs1),
    asmstr,
    []>;

  def #NAME#RRi16 : InstVRV<T16.Coding, opcode,
   (outs GPRi16:$lhs),
   (ins GPRi16:$rhs1),
   asmstr,
   []>;

  def #NAME#RRi32 : InstVRV<T32.Coding, opcode,
   (outs GPRi32:$lhs),
   (ins GPRi32:$rhs1),
   asmstr,
   []>;

  def #NAME#RRi64 : InstVRV<T64.Coding, opcode,
   (outs GPRi64:$lhs),
   (ins GPRi64:$rhs1),
   asmstr,
   []>;
}

multiclass InstRVVInt<bits<15> opcode, string asmstr>
{
  def #NAME#8 : InstRVV<T8.Coding, opcode,
    (outs GPRi8:$lhs),
    (ins),
    asmstr,
    []>;

  def #NAME#16 : InstRVV<T16.Coding, opcode,
   (outs GPRi16:$lhs),
   (ins),
   asmstr,
   []>;

  def #NAME#32 : InstRVV<T32.Coding, opcode,
   (outs GPRi32:$lhs),
   (ins ),
   asmstr,
   []>;

  def #NAME#64 : InstRVV<T64.Coding, opcode,
   (outs GPRi64:$lhs),
   (ins),
   asmstr,
   []>;
}

multiclass InstRIVInt<bits<15> opcode, string asmstr>
{
  def #NAME#8 : InstRIV32<T8.Coding, opcode,
    (outs GPRi8:$lhs),
    (ins i8imm:$rhs1),
    asmstr,
    []>;

  def #NAME#16 : InstRIV32<T16.Coding, opcode,
   (outs GPRi16:$lhs),
   (ins i16imm:$rhs1),
   asmstr,
   []>;

  def #NAME#32 : InstRIV32<T32.Coding, opcode,
   (outs GPRi32:$lhs),
   (ins i32imm:$rhs1),
   asmstr,
   []>;

/*TODO
  def #NAME#64 : InstRIV64<T64.Coding, opcode,
   (outs GPRi64:$lhs),
   (ins i64imm:$rhs1),
   asmstr,
   []>;
*/
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

/// |size|   Opcode{6}    | lh  | rh1 | Imm16                         |
/// | 0 1| 0 0 c c c c c c|d d d|x x x|i i i i i i i i i i i i i i i i|
class LumenIRInst32RI16<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst32<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<16> rh2I;

  let Inst{29-28} = 0b00;
  let Inst{27-22} = opcode;

  let Inst{21-19} = lh;
  let Inst{18-16} = rh1;
  let Inst{15-0}  = rh2I;
}

/// |size|   Opcode{6}    | Rsv | rh1 | Imm16                         |
/// | 0 1| 0 1 c c c c c c|0 0 0|x x x|i i i i i i i i i i i i i i i i|
class LumenIRInst32VRI16<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst32<outs, ins, asmstr, pattern>
{
  bits<3> rhs1;
  bits<16> rhs2I;

  let Inst{29-28} = 0b01;
  let Inst{27-22} = opcode;

  let Inst{21-19} = 0b000; //Reserved
  let Inst{18-16} = rhs1;
  let Inst{15-0}  = rhs2I;
}


/// a 64-bit LumenIR instructions
class LumenIRInst64<dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst<outs, ins, asmstr, pattern>
{
  field bits<64> Inst;
  let Inst{63-62} = 0b10;

  let Size = 8;
}



/// |size|   Opcode{6}    | lh  | rh1 | Reserved 16 | Imm32 |
/// | 1 0| 0 0 c c c c c c|d d d|x x x|0 0    ... 0 |i ... i|
class LumenIRInst64RI32<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst64<outs, ins, asmstr, pattern>
{
  bits<3> lh;
  bits<3> rh1;
  bits<32> rh2I;

  let Inst{61-60} = 0b00;
  let Inst{59-54} = opcode;

  let Inst{53-51} = lh;
  let Inst{50-48} = rh1;
  let Inst{47-32} = 0b0000000000000000; // reserved
  let Inst{31-0}  = rh2I;
}

/// |size|   Opcode{6}    | lhs | Rsv | Reserved 16 | Imm32 |
/// | 1 0| 0 1 c c c c c c|d d d|0 0 0|0 0    ... 0 |i ... i|
class LumenIRInst64I32<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst64<outs, ins, asmstr, pattern>
{
  bits<3> lhs;
  bits<32> rhs1;

  let Inst{61-60} = 0b01;
  let Inst{59-54} = opcode;

  let Inst{53-51} = lhs;
  let Inst{50-48} = 0b000; // rsv;
  let Inst{47-32} = 0b0000000000000000; // reserved
  let Inst{31-0}  = rhs1;
}

/// |size|   Opcode{6}    | lh  | Rsv | Imm16       | Imm32 |
/// | 1 0| 1 0 c c c c c c|d d d|0 0 0|i i    ... i |i ... i|
class LumenIRInst64I16I32<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst64<outs, ins, asmstr, pattern>
{
  bits<3> lhs;
  bits<16> rhs1;
  bits<32> rhs2;

  let Inst{61-60} = 0b10;
  let Inst{59-54} = opcode;

  let Inst{53-51} = lhs;
  let Inst{50-48} = 0b000; // reserved
  let Inst{47-32} = rhs1;
  let Inst{31-0}  = rhs2;
}

/// |size|   Opcode{6}    | Rsv | Rsv | Imm16       | Imm32 |
/// | 1 0| 1 1 c c c c c c|0 0 0|0 0 0|i i    ... i |i ... i|
class LumenIRInst64VI16I32<bits<6> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : LumenIRInst64<outs, ins, asmstr, pattern>
{
  bits<16> rhs1I;
  bits<32> rhs2I;

  let Inst{61-60} = 0b11;
  let Inst{59-54} = opcode;

  let Inst{53-51} = 0b000; // reserved
  let Inst{50-48} = 0b000; // reserved
  let Inst{47-32} = rhs1I;
  let Inst{31-0}  = rhs2I;
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

