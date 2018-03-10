//===-- LumenIRInstPrinter.cpp - Convert LumenIR MCInst to assembly syntax --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an LumenIR MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "LumenIRInstPrinter.h"

#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

#include <cstring>

#define DEBUG_TYPE "asm-printer"

namespace llvm {

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "LumenIRGenAsmWriter.inc"

void LumenIRInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                               StringRef Annot, const MCSubtargetInfo &STI) {
  unsigned Opcode = MI->getOpcode();

  printInstruction(MI, O);
  printAnnotation(O, Annot);
}

void LumenIRInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  const MCOperandInfo &MOI = this->MII.get(MI->getOpcode()).OpInfo[OpNo];

  if(Op.isReg()) {
    //TODO altidx??
    O << getRegisterName(Op.getReg(), 0);
  } else if (Op.isImm()) {
    O << Op.getImm();
  } else if (Op.isFPImm()) {
    O << Op.isFPImm();
  } else {
      llvm_unreachable("Unknown operand type");
  }
}

/// This is used to print an immediate value that ends up
/// being encoded as a pc-relative value.
void LumenIRInstPrinter::printPCRelImm(const MCInst *MI, unsigned OpNo,
                                   raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);

  llvm_unreachable("Not implemented");

}

void LumenIRInstPrinter::printMemri(const MCInst *MI, unsigned OpNo,
                                raw_ostream &O) {
  assert(MI->getOperand(OpNo).isReg() && "Expected a register for the first operand");

  llvm_unreachable("Not implemented");
}

} // end of namespace llvm

