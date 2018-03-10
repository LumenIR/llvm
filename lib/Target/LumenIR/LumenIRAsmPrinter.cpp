//===-- LumenIRAsmPrinter.cpp - LumenIR LLVM assembly writer ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to GAS-format LumenIR assembly language.
//
//===----------------------------------------------------------------------===//

#include "LumenIR.h"
#include "LumenIRSubtarget.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/IR/Mangler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetRegisterInfo.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define DEBUG_TYPE "lumenir-asm-printer"

using namespace llvm;

namespace llvm {

/// An LumenIR assembly code printer.
class LumenIRAsmPrinter : public AsmPrinter {
public:
  LumenIRAsmPrinter(TargetMachine &TM,
                std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), MRI(*TM.getMCRegisterInfo()) { }

  StringRef getPassName() const override { return "LumenIR Assembly Printer"; }


  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                       unsigned AsmVariant, const char *ExtraCode,
                       raw_ostream &O) override;

  bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNum,
                             unsigned AsmVariant, const char *ExtraCode,
                             raw_ostream &O) override;

  void EmitInstruction(const MachineInstr *MI) override;

private:
  const MCRegisterInfo &MRI;

  MCInst lowerInstruction(const MachineInstr &MI);

};

bool LumenIRAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                                    unsigned AsmVariant, const char *ExtraCode,
                                    raw_ostream &O) {
  llvm_unreachable("Not implemented");

  return false;
}

bool LumenIRAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI,
                                          unsigned OpNum, unsigned AsmVariant,
                                          const char *ExtraCode,
                                          raw_ostream &O) {
  llvm_unreachable("Not implemented");
}

void LumenIRAsmPrinter::EmitInstruction(const MachineInstr *MI) {
  EmitToStreamer(*OutStreamer, lowerInstruction(*MI));
}

} // end of namespace llvm

extern "C" void LLVMInitializeLumenIRAsmPrinter() {
  RegisterAsmPrinter<LumenIRAsmPrinter> X(getTheLumenIRTarget());
}


MCInst LumenIRAsmPrinter::lowerInstruction(const MachineInstr &MI) {
  MCInst Inst;
  Inst.setOpcode(MI.getOpcode());

  for (MachineOperand const &MO : MI.operands()) {
    MCOperand MCOp;

    switch (MO.getType()) {
    default:
      MI.print(errs());
      llvm_unreachable("unknown or not implemented operand type");

    case MachineOperand::MO_Register:
      // Ignore implicit operands
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;

    case MachineOperand::MO_Immediate:
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    }
    Inst.addOperand(MCOp);
  }
  return Inst;
}
