//===-- LumenIR.td - Describe the RISCV Target Machine -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

include "LumenIRRegisterInfo.td"
include "LumenIRInstrInfo.td"


def LumenIRInstrInfo : InstrInfo;


def : ProcessorModel<"lumenir", NoSchedModel, []>;


def LumenIR : Target {
  let InstructionSet = LumenIRInstrInfo;
}
