set(LLVM_TARGET_DEFINITIONS LumenIR.td)

tablegen(LLVM LumenIRGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM LumenIRGenCallingConv.inc -gen-callingconv)
tablegen(LLVM LumenIRGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM LumenIRGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM LumenIRGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LumenIRGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM LumenIRGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM LumenIRGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(LumenIRCommonTableGen)

add_llvm_target(LumenIRCodeGen
  LumenIRAsmPrinter.cpp
  LumenIRFrameLowering.cpp
  LumenIRInstrInfo.cpp
  LumenIRRegisterInfo.cpp
  LumenIRISelDAGToDAG.cpp
  LumenIRISelLowering.cpp
  LumenIRSubtarget.cpp
  LumenIRTargetMachine.cpp
  LumenIRTargetObjectFile.cpp
)

add_subdirectory(Disassembler)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(InstPrinter)

