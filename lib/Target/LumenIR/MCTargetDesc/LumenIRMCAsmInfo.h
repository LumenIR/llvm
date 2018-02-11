//===-- LumenIRMCAsmInfo.h - LumenIR Asm Info ----------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the LumenIRMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LUMENIR_MCTARGETDESC_LUMENIRMCASMINFO_H
#define LLVM_LIB_TARGET_LUMENIR_MCTARGETDESC_LUMENIRMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class LumenIRMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit LumenIRMCAsmInfo(const Triple &TargetTriple);
};

} // namespace llvm

#endif
