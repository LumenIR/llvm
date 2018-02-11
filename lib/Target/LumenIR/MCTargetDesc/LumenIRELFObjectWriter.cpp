//===-- LumenIRELFObjectWriter.cpp - LumenIR ELF Writer -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/LumenIRMCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class LumenIRELFObjectWriter : public MCELFObjectTargetWriter {
public:
  LumenIRELFObjectWriter();

  ~LumenIRELFObjectWriter() override;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

LumenIRELFObjectWriter::LumenIRELFObjectWriter()
    : MCELFObjectTargetWriter(false /*Is64Bit*/,
		    	      ELF::ELFOSABI_NONE /*OSABI*/,
			      0 /*EMachine*/,
			      false /*HasRelocationAddend*/
		             ) {}

LumenIRELFObjectWriter::~LumenIRELFObjectWriter() {}

unsigned LumenIRELFObjectWriter::getRelocType(MCContext &Ctx,
                                            const MCValue &Target,
                                            const MCFixup &Fixup,
                                            bool IsPCRel) const {
  llvm_unreachable("invalid fixup kind!");
}

MCObjectWriter *llvm::createLumenIRELFObjectWriter(raw_pwrite_stream &OS) {
  MCELFObjectTargetWriter *MOTW = new LumenIRELFObjectWriter();
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian*/ true);
}

