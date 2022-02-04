//
//  ops.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#define REG_LO(x) ((x & 0x0F) >> 0)
#define REG_HI(x) ((x & 0xF0) >> 4)

#include "cpu.h"
#include "../mmu/mmu.h"

Instruction(SET) { // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] = ctx->Registers[REG_HI(Registers)];
	return;
}
Instruction(LDWM) { // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	u64* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_READ);
	ctx->Registers[REG_LO(Registers)] = Memory[0];
}
Instruction (STWM) { // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	u64* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_WRITE);
	Memory[0] = ctx->Registers[REG_LO(Registers)];
}
Instruction (LDBM) { // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	byte* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_READ);
	ctx->Registers[REG_LO(Registers)] = Memory[0];
}
Instruction (STBM) { // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	byte* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_WRITE);
	Memory[0] = ctx->Registers[REG_LO(Registers)];
}
Instruction (OR) { // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] |= ctx->Registers[REG_HI(Registers)];
}
Instruction (AND) { // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] &= ctx->Registers[REG_HI(Registers)];
}
Instruction (XOR) { // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] ^= ctx->Registers[REG_HI(Registers)];
}
Instruction (NOT) { // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] = ~ctx->Registers[REG_HI(Registers)];
}
Instruction (ADD) { // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] += ctx->Registers[REG_HI(Registers)];
}
Instruction (SUB) { // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] -= ctx->Registers[REG_HI(Registers)];
}
Instruction (MUL) { // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] *= ctx->Registers[REG_HI(Registers)];
}
Instruction (DIV) { // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] /= ctx->Registers[REG_HI(Registers)];
}
Instruction (SETI) { // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] = Immediate;
}
Instruction (LDWMI) { // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	u64* Memory = mmu_translate(Immediate, _ACCESS_READ);
	ctx->Registers[Register] = Memory[0];
}
Instruction (STWMI) { // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	u64* Memory = mmu_translate(ctx->Registers[Register], _ACCESS_WRITE);
	Memory[0] = Immediate;
}
Instruction (LDBMI) { // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	byte* Memory = mmu_translate(Immediate, _ACCESS_READ);
	ctx->Registers[Register] = Memory[0];
}
Instruction (STBMI) { // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	byte* Memory = mmu_translate(ctx->Registers[Register], _ACCESS_WRITE);
	Memory[0] = Immediate;
}
Instruction(ORI) { // Logical OR Immediate (ORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] |= Immediate;
}
Instruction(ANDI) { // Logical AND Immediate (ANDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] &= Immediate;
}
Instruction(XORI) { // Logical XOR Immediate (XORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] ^= Immediate;
}
Instruction(ADDI) { // Sum Register and Immediate (ADDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] += Immediate;
}
Instruction(SUBI) { // Subtract Immediate from Register (SUBI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] -= Immediate;
}
Instruction(MULI) { // Multiply Register by Immediate (MULI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] *= Immediate;
}
Instruction(DIVI) { // Divide Register By Immediate (DIVI [R:(4,8),DEST] [I:(64,64),SRC]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	ctx->Registers[Register] /= Immediate;
}
Instruction(SL) { // Shift Left (SL [R:(4,4),DEST] [R:(4,4),AMT]):16
	byte Registers = r1() & 0xF;
	ctx->Registers[REG_LO(Registers)] <<= ctx->Registers[REG_HI(Registers)];
}
Instruction(SR) { // Shift Right (SR [R:(4,4),DEST] [R:(4,4),AMT]):16
	byte Registers = r1() & 0xF;
	ctx->Registers[REG_LO(Registers)] >>= ctx->Registers[REG_HI(Registers)];
}
Instruction(SLI) { // Shift Left Immediate (SLI [R:(4,8),SRC] [I:(6,8),AMT]):24
	byte Register = r1() & 0xF;
	byte Immediate = r1() & 0x3F;
	ctx->Registers[Register] <<= Immediate;
}
Instruction(SRI) { // Shift Right Immediate (SRI [R:(4,8),SRC] [I:(6,8,AMT]):24
	byte Register = r1() & 0xF;
	byte Immediate = r1() & 0x3F;
	ctx->Registers[Register] <<= Immediate;
}
Instruction(SA) { // Stack Add (Push) (SA	[R:(4,8),SRC]):16
	byte Register = r1() & 0xF;
	mmui_stackput(ctx->Registers[Register]);
}
Instruction(SP) { // Stack Pull (SP [R:(4,8),DEST]):16
	byte Register = r1() & 0xF;
	ctx->Registers[Register] = mmui_stackpull();
}
Instruction(SAI) { // Stack Add (Push) Immediate (SAI [I:(64, 64)]):72
	u64 Immediate = rx(8);
	mmui_stackput(Immediate);
}
Instruction(GO) { // Go (Jump) (GO [R:(4,8),LOCATION]):16
	byte Register = r1() & 0xF;
	ctx->ip = ctx->Registers[Register];
}
Instruction(ENT) { // Enter (Call) (GO [R:(4,8),LOCATION]):16
	byte Register = r1() & 0xF;
	mmui_stackput(ctx->ip);
	ctx->ip = ctx->Registers[Register];
}
Instruction(RT) { // Return (RT):8
	ctx->ip = mmui_stackpull();
}
Instruction(RTF) { // Return if Flag (RTF [R:(4,8),FLAG]):16
	byte Register = r1() & 0xF;
	if (ctx->sf0 & ctx->Registers[Register])
		RT();
}
Instruction(RTFI) { // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72
	byte Immediate = rx(8);
	if (ctx->sf0 & Immediate)
		RT();
}
Instruction(GOI) { // Go (Jump) Immediate (GOI [I:(64,64),LOCATION]):72
	u64 Immediate = rx(8);
	ctx->ip = Immediate;
}
Instruction(ENTI) { // Enter (Call) Immediate (ENTI [I:(64,64),LOCATION]):72
	u64 Immediate = rx(8);
	mmui_stackput(ctx->ip);
	ctx->ip = Immediate;
}
Instruction(CMP) { // Compare Registers (CMP [R:(4,4),COMPARE0] [R:(4,4),COMPARE1]):16
	byte Registers = r1();
	if (ctx->Registers[REG_LO(Registers)] > ctx->Registers[REG_HI(Registers)])
		SET_GREATFLAG(ctx->sf0);
	if (ctx->Registers[REG_LO(Registers)] < ctx->Registers[REG_HI(Registers)])
		SET_LESSFLAG(ctx->sf0);
	if (ctx->Registers[REG_LO(Registers)] == ctx->Registers[REG_HI(Registers)])
		SET_EQUALFLAG(ctx->sf0);
}
Instruction(CMPI)  { // Compare Register with Immediate (CMPI [R:(4,8),COMPARE0] [I:(64,64),COMPARE1]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	if (ctx->Registers[REG_LO(Register)] > Immediate)
		SET_GREATFLAG(ctx->sf0);
	if (ctx->Registers[REG_LO(Register)] < Immediate)
		SET_LESSFLAG(ctx->sf0);
	if (ctx->Registers[REG_LO(Register)] == Immediate)
		SET_EQUALFLAG(ctx->sf0);
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
