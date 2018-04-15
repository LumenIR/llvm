//===- LumenIRDisassembler.cpp - Disassembler for LumenIR -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is part of the AVR Disassembler.
//
//===----------------------------------------------------------------------===//

#include "LumenIR.h"
#include "LumenIRRegisterInfo.h"
#include "LumenIRSubtarget.h"
#include "MCTargetDesc/LumenIRMCTargetDesc.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "lumenir-disassembler"

using DecodeStatus = MCDisassembler::DecodeStatus;

namespace {

/// A disassembler class for LumenIR.
class LumenIRDisassembler : public MCDisassembler {
public:
  LumenIRDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}
  virtual ~LumenIRDisassembler() = default;

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &VStream,
                              raw_ostream &CStream) const override;
};
}

static MCDisassembler *createLumenIRDisassembler(const Target &T,
                                                 const MCSubtargetInfo &STI,
                                                 MCContext &Ctx) {
  return new LumenIRDisassembler(STI, Ctx);
}


extern "C" void LLVMInitializeLumenIRDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheLumenIRTarget(),
                                         createLumenIRDisassembler);
}

static constexpr uint16_t GPRDecoderTable8[] = {
  LumenIR::R0_8,
  LumenIR::R1_8,
  LumenIR::R2_8,
  LumenIR::R3_8,
  LumenIR::R4_8,
  LumenIR::R5_8,
  LumenIR::R6_8,
  LumenIR::R7_8
};

static constexpr uint16_t GPRDecoderTable16[] = {
  LumenIR::R0_16,
  LumenIR::R1_16,
  LumenIR::R2_16,
  LumenIR::R3_16,
  LumenIR::R4_16,
  LumenIR::R5_16,
  LumenIR::R6_16,
  LumenIR::R7_16
};

static constexpr uint16_t GPRDecoderTable32[] = {
  LumenIR::R0_32,
  LumenIR::R1_32,
  LumenIR::R2_32,
  LumenIR::R3_32,
  LumenIR::R4_32,
  LumenIR::R5_32,
  LumenIR::R6_32,
  LumenIR::R7_32
};

static constexpr uint16_t GPRDecoderTable64[] = {
  LumenIR::R0_64,
  LumenIR::R1_64,
  LumenIR::R2_64,
  LumenIR::R3_64,
  LumenIR::R4_64,
  LumenIR::R5_64,
  LumenIR::R6_64,
  LumenIR::R7_64
};


static DecodeStatus DecodeGPRRegisterClass(
        MCInst &Inst,
        unsigned RegNo,
        uint64_t Address,
        const void *Decoder,
        const uint16_t *GPRDecoderTable) {
  if (RegNo > 8) {
    return MCDisassembler::Fail;
  }

  unsigned Register = GPRDecoderTable[RegNo];
  Inst.addOperand(MCOperand::createReg(Register));
  return MCDisassembler::Success;
}


static DecodeStatus DecodeGPRi8RegisterClass(MCInst &Inst, unsigned RegNo,
                                             uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable8);
}

static DecodeStatus DecodeGPRi16RegisterClass(MCInst &Inst, unsigned RegNo,
                                              uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable16);
}

static DecodeStatus DecodeGPRi32RegisterClass(MCInst &Inst, unsigned RegNo,
                                              uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable32);
}

static DecodeStatus DecodeGPRi64RegisterClass(MCInst &Inst, unsigned RegNo,
                                              uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable64);
}

static DecodeStatus DecodeGPRf32RegisterClass(MCInst &Inst, unsigned RegNo,
                                              uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable32);
}

static DecodeStatus DecodeGPRf64RegisterClass(MCInst &Inst, unsigned RegNo,
                                              uint64_t Address, const void *Decoder) {
  return DecodeGPRRegisterClass(Inst, RegNo, Address, Decoder, GPRDecoderTable64);
}


#include "LumenIRGenDisassemblerTables.inc"

static const uint8_t *getDecoderTable(uint64_t Size) {

  switch (Size) {
    case  4:  return DecoderTable32;
    case  8:  return DecoderTable64;
//    case 12:  return DecoderTable96;
    default: llvm_unreachable("instructions must be 32, 64 or 96");
  }
}

DecodeStatus LumenIRDisassembler::getInstruction(
        MCInst &Instr, uint64_t &Size,
        ArrayRef<uint8_t> Bytes,
        uint64_t Address,
        raw_ostream &VStream,
        raw_ostream &CStream) const {

  uint32_t Insn = 0;

  DecodeStatus Result;

  // Try decode a 32-bit instruction.
  {
    Result = decodeInstruction(getDecoderTable(Size), Instr, Insn,
                               Address, this, STI);

    if (Result != MCDisassembler::Fail) {
      return Result;
    }

    return MCDisassembler::Fail;
  }
}

