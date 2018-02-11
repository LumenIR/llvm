#include "LumenIRELFStreamer.h"

#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/SubtargetFeature.h"
#include "llvm/Support/FormattedStream.h"

#include "LumenIRMCTargetDesc.h"

namespace llvm {

static unsigned getEFlagsForFeatureSet(const FeatureBitset &Features) {
  unsigned EFlags = 0;

  return EFlags;
}

LumenIRELFStreamer::LumenIRELFStreamer(MCStreamer &S,
                                       const MCSubtargetInfo &STI)
    : LumenIRTargetStreamer(S) {

  MCAssembler &MCA = getStreamer().getAssembler();
  unsigned EFlags = MCA.getELFHeaderEFlags();

  EFlags |= getEFlagsForFeatureSet(STI.getFeatureBits());

  MCA.setELFHeaderEFlags(EFlags);
}

} // end namespace llvm
