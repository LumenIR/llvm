//=== LumenIRCallingConv.td - Calling Conventions for LumenIR -*-tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for LumenIR architecture.
//===----------------------------------------------------------------------===//

// Use stack for arguments for the sake of simplicity
// TODO need to be reworked

//===----------------------------------------------------------------------===//
// LumenIR Return Value Calling Convention
//===----------------------------------------------------------------------===//

def RetCC_LumenIR : CallingConv
<[
//  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i8 ], CCAssignToReg<[R0_8, R1_8, R2_8, R3_8, R4_8]>>,
  CCIfType<[i16], CCAssignToReg<[R0_16, R1_16, R2_16, R3_16, R4_16]>>,
  CCIfType<[i32, f32], CCAssignToReg<[R0_32, R1_32, R2_32, R3_32, R4_32]>>
]>;


//===----------------------------------------------------------------------===//
// LumenIR Argument Calling Conventions
//===----------------------------------------------------------------------===//


// Calling convention for variadic functions.
def ArgCC_LumenIR : CallingConv
<[
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i32], CCAssignToStack<4, 4>>,
  CCIfType<[i64], CCAssignToStack<8, 4>>
]>;


//===----------------------------------------------------------------------===//
// Callee-saved register lists.
//===----------------------------------------------------------------------===//

def CSR : CalleeSavedRegs<(add R4_64, R5_64, R6_64, R7_64)>;


