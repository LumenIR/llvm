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
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7]>>,
  CCIfType<[f32], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7]>>
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

def CSR : CalleeSavedRegs<(add R0, R1, R2, R3)>;


