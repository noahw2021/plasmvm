//
//  ops.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#include "cpu.h"

Instruction(SET) { // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction(LDWM) { // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}
Instruction (STWM) { // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16

}
Instruction (LDBM) { // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16

}
Instruction (STBM) { // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}
Instruction (OR) { // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction (AND) { // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction (XOR) { // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (NOT) { // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (ADD) { // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (SUB) { // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (MUL) { // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (DIV) { // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (SETI) { // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80
	
}
Instruction (LDWMI) { // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (STWMI) { // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (LDBMI) { // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (STBMI) { // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction(ORI) { // Logical OR Immediate (ORI [R:(4,8),DEST] [I:(64,64),SRC]):80
}
Instruction(ANDI) { // Logical AND Immediate (ANDI [R:(4,8),DEST] [I:(64,64),SRC]):80
}
Instruction(XORI) { // Logical XOR Immediate (XORI [R:(4,8),DEST] [I:(64,64),SRC]):80
}
Instruction(ADDI) { // Sum Register and Immediate (ADDI [R:(4,8),DEST] [I:(64,64),SRC]):80

}
Instruction(SUBI) { // Subtract Immediate from Register (SUBI [R:(4,8),DEST] [I:(64,64),SRC]):80

}
Instruction(MULI) { // Multiply Register by Immediate (MULI [R:(4,8),DEST] [I:(64,64),SRC]):80

}
Instruction(DIVI) { // Divide Register By Immediate (DIVI [R:(4,8),DEST] [I:(64,64),SRC]):80

}
Instruction(SL) { // Shift Left (SL [R:(4,4),DEST] [R:(4,4),AMT]):16

}
Instruction(SR) { // Shift Right (SR [R:(4,4),DEST] [R:(4,4),AMT]):16

}
Instruction(SLI) { // Shift Left Immediate (SLI [R:(4,8),SRC] [I:(6,8),AMT]):24

}
Instruction(SRI) { // Shift Right Immediate (SRI [R:(4,8),SRC] [I:(6,8,AMT]):24

}
Instruction(SA) { // Stack Add (Push) (SA	[R:(4,8),SRC]):16

}
Instruction(SP) { // Stack Pull (SP [R:(4,8),DEST]):16

}
Instruction(SAI) { // Stack Add (Push) Immediate (SAI [I:(64, 64)]):72

}
Instruction(GO) { // Go (Jump) (GO [R:(4,8),LOCATION]):16

}
Instruction(ENT) { // Enter (Call) (GO [R:(4,8),LOCATION]):16

}
Instruction(RT) { // Return (RT):8

}
Instruction(RTF) { // Return if Flag (RTF [R:(4,8),FLAG]):16

}
Instruction(RTFI) { // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72

}
Instruction(GOI) { // Go (Jump) Immediate (GOI [I:(64,64),LOCATION]):72

}
Instruction(ENTI) { // Enter (Call) Immediate (ENTI [I:(64,64),LOCATION]):72

}
Instruction(CMP) { // Compare Registers (CMP [R:(4,4),COMPARE0] [R:(4,4),COMPARE1]):16

}
Instruction(CMPI)  { // Compare Register with Immediate (CMPI [R:(4,8),COMPARE0] [I:(64,64),COMPARE1]):80

}
Instruction(GOF) { // Go if Flag (GOF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16

}
Instruction(ENTF) { // Enter if Flag (ENTF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	
}
Instruction(GOFI) { // Go if Flag Immediate (GOFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80

}
Instruction(ENTFI) { // Enter if Flag Immediate (ENTFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80

}
Instruction(GOFII) { // Go if Flag Immediate Immediate  (GOFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136

}
Instruction(ENTFII) { // Enter if Flag Immediate Immediate (ENTFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136

}
Instruction(NEG) { // Signed Negate Register (NEG [R:(4,8)]):16

}
Instruction(NOP) { // No Operation (NOP):8

}
Instruction(EIH) { // Enable Interrupt Handling (EIH):8

}
Instruction(DIH) { // Disable Interrupt Handling (DIH):8

}
Instruction(HLT) { // Enter Halt State (HLT):8

}
Instruction(INT) { // Call Interrupt (INT [R:(4,8),INTERRUPT]):8

}
Instruction(INTI) { // Call Interrupt Immediate (INTI [I:(8,8),INTERRUPT]):16

}
Instruction(HND) { // Handle Interrupt (HND [R:(4,4),INTERRUPT] [R:(4,4),LOCATION]):16

}
Instruction(HNDI) { // Handle Interrupt Immediate (HNDI [I:(8,8),INTERRUPT] [R:(4,8),LOCATION]):24

}
Instruction(HNDII) { // Handle Interrupt Immediate Immediate (HNDII [I:(8,8),INTERRUPT] [I:(64,64),LOCATION]):80
}
Instruction(SPA) { // Stack Pull All (SPA):8
}
Instruction(SPG) { // Stack Pull General (SPG):8
}
Instruction(SAA) { // Stack Add (Push) All (SAA):8
}
Instruction(SAG) { // Stack Add (Push) General (SAG):8
	
}
Instruction(LDSD) { // Load System Descriptor (LDSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	
}
Instruction(LDSDI) { // Load System Descriptor Immediate (LDSDI [I:(64,64),PART0] [I:(64,64),PART1]):136
	
}
Instruction(STSD) { // Store System Descriptor to Registers (STSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	
}
Instruction(LDVM) { // Load Virtual Descriptor from Registers (LDVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	
}
Instruction(LDVMI) { // Load Virtual Descriptor from Immediates (LDVMI [I:(64,64),PART0] }[I:(64,64),PART1]):136
	
}
Instruction(STVM) { // Store Virtual Descriptor to Registers (STVM [R:(4,4),PART0] [R:(4,4),PART1]):16

}
Instruction(SPN) { // Stack Pull No Operand (SPN):8

}
Instruction(MSP) { // Subtract Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA] [I:(20,20),IMM]):32
	
}
Instruction(SSP) { // Subtract Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA]
	
}
Instruction(ASP) { // Add Stack Pointer (DATA is multiplied by IMM) (ASP [R:(4,4),DATA] [I:(20,20),IMM]):32
	
}
Instruction(SPB) { // Stack Pull Byte (SPB [R:(4,8),DEST]):16
	
}
Instruction(SAB) { // Stack Add Byte (SAB [R:(4,8),SRC]):16
	
}
Instruction(SAII) { // Stack Add Byte Immediate (SAII [I:(8,8),SRC]):16
	
}

Instruction(INC) { // Increment (INC [R:(4,8),SRC]):16
	
}

Instruction(DEC) { // Decrement (DEC [R:(4,8),SRC]):16
	
}
