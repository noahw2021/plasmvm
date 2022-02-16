//
//  cpu_ops.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#define REG_LO(x) ((x & 0x0F) >> 0)
#define REG_HI(x) ((x & 0xF0) >> 4)

#include "cpu.h"
#include "../mmu/mmu.h"
#include "../io/io.h"

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
Instruction(SA) { // Stack Add (Push) (SA [R:(4,8),SRC]):16
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
	cpui_go(ctx->Registers[Register]);
}
Instruction(ENT) { // Enter (Call) (GO [R:(4,8),LOCATION]):16
	byte Register = r1() & 0xF;
	cpui_enter(ctx->Registers[Register]);
}
Instruction(RT) { // Return (RT):8
	cpui_return();
}
Instruction(RTF) { // Return if Flag (RTF [R:(4,8),FLAG]):16
	byte Register = r1() & 0xF;
	if (ctx->sf0 & ctx->Registers[Register])
		cpui_return();
}
Instruction(RTFI) { // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72
	byte Immediate = rx(8);
	if (ctx->sf0 & Immediate)
		cpui_return();
}
Instruction(GOI) { // Go (Jump) Immediate (GOI [I:(64,64),LOCATION]):72
	u64 Immediate = rx(8);
	cpui_go(Immediate);
}
Instruction(ENTI) { // Enter (Call) Immediate (ENTI [I:(64,64),LOCATION]):72
	u64 Immediate = rx(8);
	cpui_enter(Immediate);
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
	byte Registers = r1();
	if (ctx->sf0 & ctx->Registers[REG_LO(Registers)])
		cpui_go(ctx->Registers[REG_HI(Registers)]);
}
Instruction(ENTF) { // Enter if Flag (ENTF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	byte Registers = r1();
	if (ctx->sf0 & ctx->Registers[REG_LO(Registers)])
		cpui_enter(ctx->Registers[REG_HI(Registers)]);
}
Instruction(GOFI) { // Go if Flag Immediate (GOFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	if (ctx->sf0 & ctx->Registers[Register])
		cpui_go(Immediate);
}
Instruction(ENTFI) { // Enter if Flag Immediate (ENTFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	byte Register = r1() & 0xF;
	u64 Immediate = rx(8);
	if (ctx->sf0 & ctx->Registers[Register])
		cpui_enter(Immediate);
}
Instruction(GOFII) { // Go if Flag Immediate Immediate  (GOFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	u64 Flags = rx(8);
	u64 Immediate = rx(8);
	if (ctx->sf0 & Flags)
		cpui_go(Immediate);
}
Instruction(ENTFII) { // Enter if Flag Immediate Immediate (ENTFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	u64 Flags = rx(8);
	u64 Immediate = rx(8);
	if (ctx->sf0 & Flags)
		cpui_enter(Immediate);
}
Instruction(NEG) { // Signed Negate Register (NEG [R:(4,8)]):16
	byte Register = r1() & 0xF;
	union {
		u64 Unsigned;
		i64 Signed;
	}SignedConcern;
	SignedConcern.Unsigned = ctx->Registers[Register];
	SignedConcern.Signed = (0 - SignedConcern.Signed);
	ctx->Registers[Register] = SignedConcern.Unsigned;
}
Instruction(NOP) { // No Operation (NOP):8
	return;
}
Instruction(EIH) { // Enable Interrupt Handling (EIH):8
	SET_INTFLAG(ctx->sf0);
}
Instruction(DIH) { // Disable Interrupt Handling (DIH):8
	CLR_INTFLAG(ctx->sf0);
}
Instruction(HLT) { // Enter Halt State (HLT):8
	SET_HALTFLAG(ctx->sf0);
}
Instruction(INT) { // Call Interrupt (INT [R:(4,8),INTERRUPT]):8
	byte Register = r1() & 0xF;
	cpui_fireint(ctx->Registers[Register] & 0xFF);
}
Instruction(INTI) { // Call Interrupt Immediate (INTI [I:(8,8),INTERRUPT]):16
	byte Immediate = r1();
	cpui_fireint(Immediate);
}
Instruction(HND) { // Handle Interrupt (HND [R:(4,4),INTERRUPT] [R:(4,4),LOCATION]):16
	byte Registers = r1();
	ctx->InterruptHandlers[ctx->Registers[REG_LO(Registers)]] = ctx->Registers[REG_HI(Registers)];
}
Instruction(HNDI) { // Handle Interrupt Immediate (HNDI [I:(8,8),INTERRUPT] [R:(4,8),LOCATION]):24
	byte Immediate = r1();
	byte Register = r1() & 0xF;
	ctx->InterruptHandlers[Immediate] = ctx->Registers[Register];
}
Instruction(HNDII) { // Handle Interrupt Immediate Immediate (HNDII [I:(8,8),INTERRUPT] [I:(64,64),LOCATION]):80
	byte Immediate = r1();
	word Location = rx(8);
	ctx->InterruptHandlers[Immediate] = Location;
}
Instruction(SPA) { // Stack Pull All (SPA):8
	cpui_pullall();
}
Instruction(SPG) { // Stack Pull General (SPG):8
	cpui_pullgen();
}
Instruction(SAA) { // Stack Add (Push) All (SAA):8
	cpui_pushall();
}
Instruction(SAG) { // Stack Add (Push) General (SAG):8
	cpui_pushgen();
}
Instruction(LDSD) { // Load System Descriptor (LDSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	byte Registers = r1();
	ctx->sd0 = ctx->Registers[REG_LO(Registers)];
	ctx->sd1 = ctx->Registers[REG_HI(Registers)];
}
Instruction(LDSDI) { // Load System Descriptor Immediate (LDSDI [I:(64,64),PART0] [I:(64,64),PART1]):136
	u64 Part0 = rx(8);
	u64 Part1 = rx(8);
	ctx->sd0 = Part0;
	ctx->sd1 = Part1;
}
Instruction(STSD) { // Store System Descriptor to Registers (STSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] = ctx->sd0;
	ctx->Registers[REG_HI(Registers)] = ctx->sd1;
}
Instruction(LDVM) { // Load Virtual Descriptor from Registers (LDVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	byte Registers = r1();
	ctx->vm0 = ctx->Registers[REG_LO(Registers)];
	ctx->vm1 = ctx->Registers[REG_HI(Registers)];
}
Instruction(LDVMI) { // Load Virtual Descriptor from Immediates (LDVMI [I:(64,64),PART0] }[I:(64,64),PART1]):136
	u64 Part0 = rx(8);
	u64 Part1 = rx(8);
	ctx->vm0 = Part0;
	ctx->vm1 = Part1;
}
Instruction(STVM) { // Store Virtual Descriptor to Registers (STVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	byte Registers = r1();
	ctx->Registers[REG_LO(Registers)] = ctx->vm0;
	ctx->Registers[REG_HI(Registers)] = ctx->vm1;
}
Instruction(SPN) { // Stack Pull No Operand (SPN):8
	mmui_stackpull();
}
Instruction(MSP) { // Multiply Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA] [I:(20,20),IMM]):32
	word RawData = rx(3) & 0xFFFFFF;
	byte Register = (RawData & 0xF00000) >> 20;
	word Immediate = (RawData & 0x0FFFFF) >> 00;
	ctx->sp *= (ctx->Registers[Register] * Immediate);
}
Instruction(SSP) { // Subtract Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA]
	word RawData = rx(3) & 0xFFFFFF;
	byte Register = (RawData & 0xF00000) >> 20;
	word Immediate = (RawData & 0x0FFFFF) >> 00;
	ctx->sp -= (ctx->Registers[Register] * Immediate);
}
Instruction(ASP) { // Add Stack Pointer (DATA is multiplied by IMM) (ASP [R:(4,4),DATA] [I:(20,20),IMM]):32
	word RawData = rx(3) & 0xFFFFFF;
	byte Register = (RawData & 0xF00000) >> 20;
	word Immediate = (RawData & 0x0FFFFF) >> 00;
	ctx->sp += (ctx->Registers[Register] * Immediate);
}
Instruction(SPB) { // Stack Pull Byte (SPB [R:(4,8),DEST]):16
	byte Register = r1() & 0xF;
	ctx->Registers[Register] = mmui_stackpullbyte();
}
Instruction(SAB) { // Stack Add Byte (SAB [R:(4,8),SRC]):16
	byte Register = r1() & 0xF;
	mmui_stackputbyte(ctx->Registers[Register]);
}
Instruction(SAII) { // Stack Add Byte Immediate (SAII [I:(8,8),SRC]):16
	byte Immediate = r1();
	mmui_stackputbyte(Immediate);
}

Instruction(INC) { // Increment (INC [R:(4,8),SRC]):16
	byte Register = r1() & 0xF;
	ctx->Registers[Register]++;
}

Instruction(DEC) { // Decrement (DEC [R:(4,8),SRC]):16
	byte Register = r1() & 0xF;
	ctx->Registers[Register]--;
}

Instruction(SBN) { // Stack Pull Byte No Operand (SBN):8
	mmui_stackpullbyte();
}

Instruction(IOB) { // I/O Output Byte (IOB [R:(4,4),PORT] [R:(4,4),DATA]):16
	byte Registers = r1();
	io_data(REG_LO(Registers), REG_HI(Registers));
}

Instruction(IIB) { // I/O Input Byte (IIB [R:(4,4),PORT] [R:(4,4),DATA]):16
	byte Registers = r1();
	ctx->Registers[REG_HI(Registers)] = io_get(REG_LO(Registers));
}

Instruction(IOW) { // I/O Output Word (IOW [R:(4,4),PORT] [R:(4,4),DATA]):16
	byte Registers = r1();
	union {
		u64 Big;
		byte Small[8];
	}BigData;
	BigData.Big = ctx->Registers[REG_HI(Registers)];
	for (int i = 0; i < 8; i++)
		io_data(REG_LO(Registers), BigData.Small[i]);
}

Instruction(IIW) { // I/O Input Word (IIW [R:(4,4),PORT] [R:(4,4),DATA]):16
	byte Registers = r1();
	union {
		u64 Big;
		byte Small[8];
	}BigData;
	BigData.Big = 0;
	for (int i = 0; i < 8; i++)
		BigData.Small[i] = io_get(REG_LO(Registers));
	ctx->Registers[REG_HI(Registers)] = BigData.Big;
}

Instruction(IOS) { // I/O Output String (IOB [R:(4,4),PORT] [R:(4,4),DATA] [R:(4,8),LEN]):24
	byte Registers0 = r1();
	byte Registers1 = r1() & 0xF;
	for (int i = 0; i < Registers1; i++)
		io_data(REG_LO(Registers0), ((byte*)mmu_translate(REG_HI(Registers0), _ACCESS_READ))[i]);
}

Instruction(IIS) { // I/O Input String (IOB [R:(4,4),PORT] [R:(4,4),STR] [R:(4,8),LEN]):24
	byte Registers0 = r1();
	byte Registers1 = r1() & 0xF;
	for (int i = 0; i < Registers1; i++)
		((byte*)mmu_translate(REG_HI(Registers0), _ACCESS_READ))[i] = io_get(REG_LO(Registers0));
}

Instruction(LDQM) { // Load Register Quarter-Word from Memory (LDQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}

Instruction(LDHM) { // Load Register Half-Word from Memory (LDHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}

Instruction(STQM) { // Store Register Quarter-Word from Memory (STQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}

Instruction(STHM) { // Store Register Half-Word in Memory (STHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}

Instruction(LDQMI) { // Load Immediate Quarter-Word from Memory (LDQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	
}

Instruction(LDHMI) { // Load Immediate Half-Word from Memory (LDHM [R:(4,8),DEST] [I:(32,32),SRC]):48
	
}

Instruction(STQMI) { // Store Immediate Quarter-Word from Memory (STQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	
}

Instruction(STHMI) { // Store Immediate Half-Word in Memory (STHM [R:(4,8),DEST] [I:(32,32),SRC):48
	
}
