//===-- LumenIRInstrInfo.h - LumenIR Instruction Information ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LumenIR implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LumenIR_INSTR_INFO_H
#define LLVM_LumenIR_INSTR_INFO_H

#include "llvm/Target/TargetInstrInfo.h"

#include "LumenIRRegisterInfo.h"

#define GET_INSTRINFO_HEADER
#include "LumenIRGenInstrInfo.inc"
#undef GET_INSTRINFO_HEADER

namespace llvm {

namespace LumenIRCC {

/// LumenIR condition codes. Copy of LLVM IR codes
/// These correspond to `LumenIR_*_COND` in `LumenIRInstrInfo.td`.
/// They must be kept in synch.
enum CondCodes {
  //TODO
  COND_INVALID
};

} // end of namespace LumenIRCC

namespace LumenIRII {

/// Specifies a target operand flag.
enum TOF {
  MO_NO_FLAG,

  /// On a symbol operand, this represents the lo part.
  MO_LO = (1 << 1),

  /// On a symbol operand, this represents the hi part.
  MO_HI = (1 << 2),

  /// On a symbol operand, this represents it has to be negated.
  MO_NEG = (1 << 3)
};

} // end of namespace LumenIRII

/// Utilities related to the LumenIR instruction set.
class LumenIRInstrInfo : public LumenIRGenInstrInfo {
public:
  explicit LumenIRInstrInfo();

  const LumenIRRegisterInfo &getRegisterInfo() const { return RI; }
  unsigned getInstSizeInBytes(const MachineInstr &MI) const override;

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const DebugLoc &DL, unsigned DestReg, unsigned SrcReg,
                   bool KillSrc) const override;
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, unsigned SrcReg,
                           bool isKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;
  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, unsigned DestReg,
                            int FrameIndex, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;

  // Branch analysis.
  bool analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TBB,
                     MachineBasicBlock *&FBB,
                     SmallVectorImpl<MachineOperand> &Cond,
                     bool AllowModify = false) const override;
  unsigned insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
                        MachineBasicBlock *FBB, ArrayRef<MachineOperand> Cond,
                        const DebugLoc &DL,
                        int *BytesAdded = nullptr) const override;
  unsigned removeBranch(MachineBasicBlock &MBB,
                        int *BytesRemoved = nullptr) const override;
  bool
  reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const override;

  MachineBasicBlock *getBranchDestBlock(const MachineInstr &MI) const override;


private:
  const LumenIRRegisterInfo RI;
};

} // end namespace llvm

#endif // LLVM_LumenIR_INSTR_INFO_H
