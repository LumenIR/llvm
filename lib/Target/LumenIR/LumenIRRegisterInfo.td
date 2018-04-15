//===-- LumenIRRegisterInfo.td - LumenIR Register defs -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the LumenIR register file
//===----------------------------------------------------------------------===//

// General purpose register definition.
class LumenIRReg<bits<3> num,
             string name,
             list<Register> subregs = [],
             list<string> altNames = []>
  : RegisterWithSubRegs<name, subregs>
{
  field bits<3> Num = num;

  let HWEncoding{2-0} = num;
  let Namespace = "LumenIR";
  let SubRegs = subregs;
  let AltNames = altNames;
}

// Special registers definition
class LumenIRSpecReg<bits<5> num,
                     string name,
                     list<Register> subregs = [],
                     list<string> altNames = []>
  : RegisterWithSubRegs<name, subregs>
{
  field bits<5> Num = num;
  let HWEncoding{4-0} = num;

  let Namespace = "LumenIR";
  let AltNames = altNames;
}

// Subregister indices.
let Namespace = "LumenIR" in
{
  def sub_8  : SubRegIndex<8>;
  def sub_16 : SubRegIndex<16>;
  def sub_32 : SubRegIndex<32>;

}

let Namespace = "LumenIR" in {
  def ptr : RegAltNameIndex;
}


//===----------------------------------------------------------------------===//
//  8-bit general purpose registers
//===----------------------------------------------------------------------===//

// Special regs, accessable only by special instructions

def PC    : LumenIRSpecReg<0, "PC">    , DwarfRegNum<[0]>;
def SP    : LumenIRSpecReg<1, "SP">    , DwarfRegNum<[1]>;
def FP    : LumenIRSpecReg<2, "FP">    , DwarfRegNum<[2]>;
def FLAGS : LumenIRSpecReg<3, "FLAGS"> , DwarfRegNum<[3]>;
def RV    : LumenIRSpecReg<4, "RV">    , DwarfRegNum<[4]>;
def RA    : LumenIRSpecReg<5, "RA">    , DwarfRegNum<[5]>;



def R0_8  : LumenIRReg<0,  "R0:8">,  DwarfRegNum<[16]>;
def R1_8  : LumenIRReg<1,  "R1:8">,  DwarfRegNum<[17]>;
def R2_8  : LumenIRReg<2,  "R2:8">,  DwarfRegNum<[18]>;
def R3_8  : LumenIRReg<3,  "R3:8">,  DwarfRegNum<[19]>;
def R4_8  : LumenIRReg<4,  "R4:8">,  DwarfRegNum<[20]>;
def R5_8  : LumenIRReg<5,  "R5:8">,  DwarfRegNum<[21]>;
def R6_8  : LumenIRReg<6,  "R6:8">,  DwarfRegNum<[22]>;
def R7_8  : LumenIRReg<7,  "R7:8">,  DwarfRegNum<[23]>;


let SubRegIndices = [sub_8], CoveredBySubRegs = 1 in
{
  def R0_16 : LumenIRReg<0, "R0:16",  [R0_8]>, DwarfRegNum<[32]>;
  def R1_16 : LumenIRReg<1, "R1:16",  [R1_8]>, DwarfRegNum<[32]>;
  def R2_16 : LumenIRReg<2, "R2:16",  [R2_8]>, DwarfRegNum<[32]>;
  def R3_16 : LumenIRReg<3, "R3:16",  [R3_8]>, DwarfRegNum<[32]>;
  def R4_16 : LumenIRReg<4, "R4:16",  [R4_8]>, DwarfRegNum<[32]>;
  def R5_16 : LumenIRReg<5, "R5:16",  [R5_8]>, DwarfRegNum<[32]>;
  def R6_16 : LumenIRReg<6, "R6:16",  [R6_8]>, DwarfRegNum<[32]>;
  def R7_16 : LumenIRReg<7, "R7:16",  [R7_8]>, DwarfRegNum<[32]>;
}

let SubRegIndices = [sub_16], CoveredBySubRegs = 1 in
{
  def R0_32 : LumenIRReg<0, "R0:32",  [R0_16]>, DwarfRegNum<[32]>;
  def R1_32 : LumenIRReg<1, "R1:32",  [R1_16]>, DwarfRegNum<[32]>;
  def R2_32 : LumenIRReg<2, "R2:32",  [R2_16]>, DwarfRegNum<[32]>;
  def R3_32 : LumenIRReg<3, "R3:32",  [R3_16]>, DwarfRegNum<[32]>;
  def R4_32 : LumenIRReg<4, "R4:32",  [R4_16]>, DwarfRegNum<[32]>;
  def R5_32 : LumenIRReg<5, "R5:32",  [R5_16]>, DwarfRegNum<[32]>;
  def R6_32 : LumenIRReg<6, "R6:32",  [R6_16]>, DwarfRegNum<[32]>;
  def R7_32 : LumenIRReg<7, "R7:32",  [R7_16]>, DwarfRegNum<[32]>;
}

let SubRegIndices = [sub_32], CoveredBySubRegs = 1 in
{
  def R0_64 : LumenIRReg<0, "R0:64",  [R0_32]>, DwarfRegNum<[32]>;
  def R1_64 : LumenIRReg<1, "R1:64",  [R1_32]>, DwarfRegNum<[32]>;
  def R2_64 : LumenIRReg<2, "R2:64",  [R2_32]>, DwarfRegNum<[32]>;
  def R3_64 : LumenIRReg<3, "R3:64",  [R3_32]>, DwarfRegNum<[32]>;
  def R4_64 : LumenIRReg<4, "R4:64",  [R4_32]>, DwarfRegNum<[32]>;
  def R5_64 : LumenIRReg<5, "R5:64",  [R5_32]>, DwarfRegNum<[32]>;
  def R6_64 : LumenIRReg<6, "R6:64",  [R6_32]>, DwarfRegNum<[32]>;
  def R7_64 : LumenIRReg<7, "R7:64",  [R7_32]>, DwarfRegNum<[32]>;
}


//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//


def GPRi8 : RegisterClass<"LumenIR", [i8], 8,
  (
    add R0_8, R1_8, R2_8, R3_8, R4_8, R5_8, R6_8, R7_8
  )>;

def GPRi16 : RegisterClass<"LumenIR", [i16], 16,
  (
    add R0_16, R1_16, R2_16, R3_16, R4_16, R5_16, R6_16, R7_16
  )>;

def GPRi32 : RegisterClass<"LumenIR", [i32], 32,
  (
    add R0_32, R1_32, R2_32, R3_32, R4_32, R5_32, R6_32, R7_32
  )>;

def GPRf32 : RegisterClass<"LumenIR", [f32], 32,
  (
    add R0_32, R1_32, R2_32, R3_32, R4_32, R5_32, R6_32, R7_32
  )>;

def GPRi64 : RegisterClass<"LumenIR", [i64, f64], 64,
  (
    add R0_64, R1_64, R2_64, R3_64, R4_64, R5_64, R6_64, R7_64
  )>;

def GPRf64 : RegisterClass<"LumenIR", [f64], 64,
  (
    add R0_64, R1_64, R2_64, R3_64, R4_64, R5_64, R6_64, R7_64
  )>;



def FLAGSclass : RegisterClass<"LumenIR", [i1], 1,
  (
    add FLAGS
  )>;

def sRVclass : RegisterClass<"LumenIR", [i32, f32], 32,
  (
    add RV
  )>;

