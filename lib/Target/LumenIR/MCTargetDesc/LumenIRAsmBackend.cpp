//===-- LumenIRAsmBackend.cpp - LumenIR Assembler Backend ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/LumenIRMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
class LumenIRAsmBackend : public MCAsmBackend {

public:
  LumenIRAsmBackend()
      : MCAsmBackend() {}
  ~LumenIRAsmBackend() override {}

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved) const override;

  MCObjectWriter *createObjectWriter(raw_pwrite_stream &OS) const override;

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }

  unsigned getNumFixupKinds() const override { return 1; }

  bool mayNeedRelaxation(const MCInst &Inst) const override { return false; }

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {

    llvm_unreachable("LumenIRAsmBackend::relaxInstruction() unimplemented");
  }

  bool writeNopData(uint64_t Count, MCObjectWriter *OW) const override;
};

bool LumenIRAsmBackend::writeNopData(uint64_t Count, MCObjectWriter *OW) const {
  llvm_unreachable("Not implemented");
  return true;
}

void LumenIRAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                 const MCValue &Target,
                                 MutableArrayRef<char> Data, uint64_t Value,
                                 bool IsResolved) const {
  return;
}

MCObjectWriter *
LumenIRAsmBackend::createObjectWriter(raw_pwrite_stream &OS) const {
  return createLumenIRELFObjectWriter(OS);
}

} // end anonymous namespace

MCAsmBackend *llvm::createLumenIRAsmBackend(const Target &T,
                                          const MCRegisterInfo &MRI,
                                          const Triple &TT, StringRef CPU,
                                          const MCTargetOptions &Options) {
  return new LumenIRAsmBackend();
}


