//===-- LumenIRRegisterInfo.td - LumenIR Register defs -------------*- tablegen -*-===//
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
class LumenIRSpecReg<string name, list<string> altNames = []> : Register<name>
{
  let Namespace = "LumenIR";
  let AltNames = altNames;
}

// Subregister indices.
let Namespace = "LumenIR" in
{
  def sub_d0 : SubRegIndex<32>;
  def sub_d1 : SubRegIndex<32, 32>;

  def sub_q0 : SubRegIndex<32>;
  def sub_q1 : SubRegIndex<32, 32>;
  def sub_q2 : SubRegIndex<32, 64>;
  def sub_q3 : SubRegIndex<32, 96>;
}

let Namespace = "LumenIR" in {
  def ptr : RegAltNameIndex;
}


//===----------------------------------------------------------------------===//
//  8-bit general purpose registers
//===----------------------------------------------------------------------===//

// Special regs, accessable only by special instructions

def PC    : LumenIRSpecReg<"PC">    , DwarfRegNum<[0]>;
def SP    : LumenIRSpecReg<"SP">    , DwarfRegNum<[1]>;
def FP    : LumenIRSpecReg<"FP">    , DwarfRegNum<[2]>;
def FLAGS : LumenIRSpecReg<"FLAGS"> , DwarfRegNum<[3]>;

// 32 bit GPR regs, accessable by Move,Load and store directly encoded by 3 bits

def R0  : LumenIRReg<0,  "R0">,  DwarfRegNum<[16]>;
def R1  : LumenIRReg<1,  "R1">,  DwarfRegNum<[17]>;
def R2  : LumenIRReg<2,  "R2">,  DwarfRegNum<[18]>;
def R3  : LumenIRReg<3,  "R3">,  DwarfRegNum<[19]>;
def R4  : LumenIRReg<4,  "R4">,  DwarfRegNum<[20]>;
def R5  : LumenIRReg<5,  "R5">,  DwarfRegNum<[21]>;
def R6  : LumenIRReg<6,  "R6">,  DwarfRegNum<[22]>;
def R7  : LumenIRReg<7,  "R7">,  DwarfRegNum<[23]>;

// 64 bit Quad GPR regs, encoded by number of lo part

let SubRegIndices = [sub_d0, sub_d1], CoveredBySubRegs = 1 in
{
  def R1_0 : LumenIRReg<0, "R1:0",  [R0, R1]>, DwarfRegNum<[32]>;
  def R3_2 : LumenIRReg<2, "R3:2",  [R2, R3]>, DwarfRegNum<[33]>;
  def R5_4 : LumenIRReg<4, "R5:4",  [R4, R5]>, DwarfRegNum<[34]>;
  def R7_6 : LumenIRReg<6, "R7:6",  [R6, R7]>, DwarfRegNum<[35]>;
}

//128 bit Double GPR regs, encoded by number of lo part

let SubRegIndices = [sub_q0, sub_q1, sub_q2, sub_q3], CoveredBySubRegs = 1 in
{
  def R3_0 : LumenIRReg<0, "R3:0",  [R0, R1, R2, R3]>, DwarfRegNum<[64]>;
  def R7_4 : LumenIRReg<4, "R7:4",  [R4, R5, R6, R7]>, DwarfRegNum<[65]>;
}

//TODO maybe we should add additional long vector registers ?

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

//TODO what about i1, i8, v4i8, i16, v2i16?

def sGPR : RegisterClass<"LumenIR", [i32,f32], 32,
  (
    add R0, R1, R2, R3, R4, R5, R6, R7
  )>;

def dGPR : RegisterClass<"LumenIR", [i64, v2i32, f32, v2f32], 64,
  (
    add R1_0, R3_2, R5_4, R7_6
  )>;

def qGPR : RegisterClass<"LumenIR", [v4i32, v4f32, v2i32, v2i64], 128,
  (
    add R3_0, R7_4
  )>;

def FLAGSclass : RegisterClass<"LumenIR", [i1], 1,
  (
    add FLAGS
  )>;


