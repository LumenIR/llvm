//===-- LumenIRTargetObjectFile.h - LumenIR Object Info -----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_TARGET_OBJECT_FILE_H
#define LLVM_LUMENIR_TARGET_OBJECT_FILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// Lowering for an LumenIR ELF32 object file.
class LumenIRTargetObjectFile : public TargetLoweringObjectFileELF {

};

} // end namespace llvm

#endif // LLVM_LumenIR_TARGET_OBJECT_FILE_H
