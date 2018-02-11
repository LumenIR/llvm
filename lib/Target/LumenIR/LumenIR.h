//===-- LumenIR.h - Top-level interface for LumenIR representation ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// LumenIR back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LUMENIR_H
#define LLVM_LUMENIR_H

#include "LumenIRSubtarget.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class LumenIRTargetMachine;
class FunctionPass;

FunctionPass *createLumenIRISelDag(LumenIRTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);


/// Contains the LumenIR backend.
namespace LumenIR {


} // end of namespace LumenIR

} // end namespace llvm

#endif // LLVM_LUMENIR_H
