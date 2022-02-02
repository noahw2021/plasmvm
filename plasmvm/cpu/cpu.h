//
//  cpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef cpu_h
#define cpu_h

/*
 Instructions in enum follow the below format
 NAME[tab]= 0xNN, // DESCRIPTION (NAME [(R|I,D):(PSZ,USZ)]):TISZ
 
 Where NAME is the Instruction's name
 Where DESCRIPTION is the Instruction's functional description
 Where (R|I) represents R or I depending on if the value is a register or immediate
 Where D is the Operand's name
 Where PSZ is the allocated size of the operand in bits
 Where USZ is the usable size of the operand in bits
 Where TISZ is the total size of the instruction in bits
 Where NN is the total size of the opcode. See example below.
 
 Differences between PSZ and USZ occur when needed to be used as padding when an instruction's argument size in bits not divisible by 8 (or byte size on architecture).
 
 Example:
 
 MOV[tab]= 0x00, // Moves an operand into a register (MOV [R:(4,8),DEST] [I:(64,64),SRC]):80
 
 Where "MOV" is the Instruction's name
 Where "Moves an operand into a register" is the Instruction's description
 Where "[R:(4,8),DEST]" signifies that the operand "DEST" is a register physically stored in 8 bits but only 4 should be used by the instruction.
 Where "I:(64,64),SRC]" signifies that the operand "SRC" is an immediate value physically stored in 64 bits and that all 64 bits are available to be used by the compiler.
 Where ":80" signifies that the instruction is in total 80 bits long. This is determined by (8 + 8 + 64), with 8 being the size of the opcode, 8 being the size of the 1st operand and 64 being the size of the 2nd operand.
 Where "00" signifies the opcode's value. May be larger or smaller than 8 bits. Zeros should be used to prefix the size if it cannot be represented (Each instruction must have the same opcode length).
 */

enum {
	__SET, // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	__LDWM, // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STWM, // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__LDBM, // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STBM, // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__OR, // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16
	__AND, // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16
	__XOR, // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16
	__NOT, // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16
	__ADD, // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16
	__SUB, // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16
	__MUL, // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16
	__DIV, // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16
	__SETI, // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__LDWMI, // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__STWMI, // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__LDBMI, // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__STBMI, // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__ORI, // Logical OR Immediate (ORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__ANDI, // Logical AND Immediate (ANDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__XORI, // Logical XOR Immediate (XORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__ADDI, // Sum Register and Immediate (ADDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__SUBI, // Subtract Immediate from Register (SUBI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__MULI, // Multiply Register by Immediate (MULI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__DIVI, // Divide Register By Immediate (DIVI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__SL, // Shift Left (SL [R:(4,4),DEST] [R:(4,4),AMT]):16
	__SR, // Shift Right (SR [R:(4,4),DEST] [R:(4,4),AMT]):16
	__SLI, // Shift Left Immediate (SLI [R:(4,8),SRC] [I:(6,8),AMT]):24
	__SRI, // Shift Right Immediate (SRI [R:(4,8),SRC] [I:(6,8,AMT]):24
	__SA, // Stack Add (Push) (SA	[R:(4,8),SRC]):16
	__SP, // Stack Pull (SP [R:(4,8),DEST]):16
	__SAI, // Stack Add (Push) Immediate (SAI [I:(64, 64)]):72
	__GO, // Go (Jump) (GO [R:(4,8),LOCATION]):16
	__ENT, // Enter (Call) (GO [R:(4,8),LOCATION]):16
	__RT, // Return (RT):8
	__RTF, // Return if Flag (RTF [R:(4,8),FLAG]):16
	__RTFI, // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72
	__GOI, // Go (Jump) Immediate (GOI [I:(64,64),LOCATION]):72
	__ENTI, // Enter (Call) Immediate (ENTI [I:(64,64),LOCATION]):72
	__CMP, // Compare Registers (CMP [R:(4,4),COMPARE0] [R:(4,4),COMPARE1]):16
	__CMPI, // Compare Register with Immediate (CMPI [R:(4,8),COMPARE0] [I:(64,64),COMPARE1]):80
	__GOF, // Go if Flag (GOF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	__ENTF, // Enter if Flag (ENTF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	__GOFI, // Go if Flag Immediate (GOFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	__ENTFI, // Enter if Flag Immediate (ENTFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	__GOFII, // Go if Flag Immediate Immediate  (GOFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	__ENTFII, // Enter if Flag Immediate Immediate (ENTFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	__NEG, // Signed Negate Register (NEG [R:(4,8)]):16
	__NOP, // No Operation (NOP):8
	__EIH, // Enable Interrupt Handling (EIH):8
	__DIH, // Disable Interrupt Handling (DIH):8
	__HLT, // Enter Halt State (HLT):8
	__INT, // Call Interrupt (INT [R:(4,8),INTERRUPT]):8
	__INTI, // Call Interrupt Immediate (INTI [I:(8,8),INTERRUPT]):16
	__HND, // Handle Interrupt (HND [R:(4,4),INTERRUPT] [R:(4,4),LOCATION]):16
	__HNDI, // Handle Interrupt Immediate (HNDI [I:(8,8),INTERRUPT] [R:(4,8),LOCATION]):24
	__HNDII, // Handle Interrupt Immediate Immediate (HNDII [I:(8,8),INTERRUPT] [I:(64,64),LOCATION]):80
	__SPA, // Stack Pull All (SPA):8
	__SPG, // Stack Pull General (SPG):8
	__SAA, // Stack Add (Push) All (SAA):8
	__SAG, // Stack Add (Push) General (SAG):8
	__LDSD, // Load System Descriptor (LDSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDSDI, // Load System Descriptor Immediate (LDSDI [I:(64,64),PART0] [I:(64,64),PART1]):136
	__STSD, // Store System Descriptor to Registers (STSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDVM, // Load Virtual Descriptor from Registers (LDVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDVMI, // Load Virtual Descriptor from Immediates (LDVMI [I:(64,64),PART0] [I:(64,64),PART1]):136
	__STVM, // Store Virtual Descriptor to Registers (STVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	__SPN, // Stack Pull No Operand (SPN):8
};

extern void(*InstructionHandlers[256])(void);

#define Instruction(Name) void Name(void)
#define ListInstruction(Name) [__##Name] = Name,

#endif /* cpu_h */
