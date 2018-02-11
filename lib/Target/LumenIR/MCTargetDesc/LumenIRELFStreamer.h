//===----- LumenIRELFStreamer.h - LumenIR Target Streamer --------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_ELF_STREAMER_H
#define LLVM_LUMENIR_ELF_STREAMER_H

#include "LumenIRTargetStreamer.h"

namespace llvm {

/// A target streamer for an LumenIR ELF object file.
class LumenIRELFStreamer : public LumenIRTargetStreamer {
public:
  LumenIRELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

  MCELFStreamer &getStreamer() {
    return static_cast<MCELFStreamer &>(Streamer);
  }
};

} // end namespace llvm

#endif
