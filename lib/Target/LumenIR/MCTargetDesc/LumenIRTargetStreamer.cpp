//===-- LumenIRTargetStreamer.cpp - LumenIR Target Streamer Methods ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides LumenIR specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "LumenIRTargetStreamer.h"

#include "llvm/MC/MCContext.h"

namespace llvm {

LumenIRTargetStreamer::LumenIRTargetStreamer(MCStreamer &S)
    : MCTargetStreamer(S) {}

LumenIRTargetAsmStreamer::LumenIRTargetAsmStreamer(MCStreamer &S)
    : LumenIRTargetStreamer(S) {}

} // end namespace llvm

