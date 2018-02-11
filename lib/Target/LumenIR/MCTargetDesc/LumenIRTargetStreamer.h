//===-- LumenIRTargetStreamer.h - LumenIR Target Streamer ----------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_TARGET_STREAMER_H
#define LLVM_LUMENIR_TARGET_STREAMER_H

#include "llvm/MC/MCELFStreamer.h"

namespace llvm {
class MCStreamer;

//TODO ELFStreamer ?
/// A generic LumenIR target output stream.
class LumenIRTargetStreamer : public MCTargetStreamer {
public:
  explicit LumenIRTargetStreamer(MCStreamer &S);
};

/// A target streamer for textual LumenIR assembly code.
class LumenIRTargetAsmStreamer : public LumenIRTargetStreamer {
public:
  explicit LumenIRTargetAsmStreamer(MCStreamer &S);
};

} // end namespace llvm

#endif // LLVM_LUMENIR_TARGET_STREAMER_H
