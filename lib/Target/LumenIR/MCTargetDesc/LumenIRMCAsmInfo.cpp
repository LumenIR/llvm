//===-- LumenIRMCAsmInfo.cpp - LumenIR Asm properties -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the LumenIRMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "LumenIRMCAsmInfo.h"
#include "llvm/ADT/Triple.h"
using namespace llvm;

void LumenIRMCAsmInfo::anchor() {}

LumenIRMCAsmInfo::LumenIRMCAsmInfo(const Triple &TT) {
  CommentString = "#";
  AlignmentIsInBytes = true;
  SupportsDebugInformation = false;
}
