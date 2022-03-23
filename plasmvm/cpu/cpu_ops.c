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
#include "../fpu/fpu.h"

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
	byte Registers = r1();
	u16* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_READ);
	ctx->Registers[REG_LO(Registers)] = Memory[0];
}

Instruction(LDHM) { // Load Register Half-Word from Memory (LDHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	u32* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_READ);
	ctx->Registers[REG_LO(Registers)] = Memory[0];
}

Instruction(STQM) { // Store Register Quarter-Word from Memory (STQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	u16* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_WRITE);
	Memory[0] = ctx->Registers[REG_LO(Registers)];
}

Instruction(STHM) { // Store Register Half-Word in Memory (STHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	byte Registers = r1();
	u32* Memory = mmu_translate(ctx->Registers[REG_HI(Registers)], _ACCESS_WRITE);
	Memory[0] = ctx->Registers[REG_LO(Registers)];
}

Instruction(LDQMI) { // Load Immediate Quarter-Word from Memory (LDQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	byte Register = r1();
	u16 Immediate = rx(2);
	u16* Memory = mmu_translate(Immediate, _ACCESS_READ);
	ctx->Registers[Register] = Memory[0];
}

Instruction(LDHMI) { // Load Immediate Half-Word from Memory (LDHM [R:(4,8),DEST] [I:(32,32),SRC]):48
	byte Register = r1();
	u32 Immediate = rx(4);
	u32* Memory = mmu_translate(Immediate, _ACCESS_READ);
	ctx->Registers[Register] = Memory[0];
}

Instruction(STQMI) { // Store Immediate Quarter-Word in Memory (STQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	byte Register = r1();
	u16 Immediate = rx(2);
	u16* Memory = mmu_translate(Register, _ACCESS_WRITE);
	Memory[0] = Immediate;
}

Instruction(STHMI) { // Store Immediate Half-Word in Memory (STHM [R:(4,8),DEST] [I:(32,32),SRC):48
	byte Register = r1();
	u32 Immediate = rx(2);
	u32* Memory = mmu_translate(Register, _ACCESS_WRITE);
	Memory[0] = Immediate;
}

Instruction(STWMII) { // Store Immediate Immediate Word in Memory (STWMII [I:(64,64),DEST] [I:(64,64),SRC]):136
	u64 ImmediateDest = rx(8);
	u64 ImmediateSource = rx(8);
	u64* Memory = mmu_translate(ImmediateDest, _ACCESS_WRITE);
	Memory[0] = ImmediateSource;
}
Instruction(STHMII) { // Store Immediate Immediate Half Word in Memory (STHMII [I:(64,64),DEST] [I:(32,32),SRC]):104
	u64 ImmediateDest = rx(8);
	u32 ImmediateSource = rx(4);
	u32* Memory = mmu_translate(ImmediateDest, _ACCESS_WRITE);
	Memory[0] = ImmediateSource;
}
Instruction(STQMII) { // Store Immediate Immediate Quarter Word in Memory (STQMII [I:(64,64),DEST] [I:(16,16),SRC]):88
	u64 ImmediateDest = rx(8);
	u16 ImmediateSource = rx(2);
	u16* Memory = mmu_translate(ImmediateDest, _ACCESS_WRITE);
	Memory[0] = ImmediateSource;
}
Instruction(STBMII) { // Store Immediate Immediate Byte in Memory (STBMII [I:(64,64),DEST] [I:(8,8),SRC]):80
	u64 ImmediateDest = rx(8);
	byte ImmediateSource = rx(1);
	byte* Memory = mmu_translate(ImmediateDest, _ACCESS_WRITE);
	Memory[0] = ImmediateSource;
}
Instruction(FINC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] += 1.0f;
	else
		ctx->FPR_SINGLE[Register] += 1.0f;
	return;
} // = 0x8F, // Floating Increment (FINC [F:(4,8),REG]):16

Instruction(FDEC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] -= 1.0f;
	else
		ctx->FPR_SINGLE[Register] -= 1.0f;
	return;
} // = 0x90, // Floating Decrement (FDEC [F:(4,8),REG]):16

Instruction(FNEG) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] = fpud_abs(ctx->FPR_DOUBLE[Register]) * -1.0f;
	else
		ctx->FPR_SINGLE[Register] = fpus_abs(ctx->FPR_SINGLE[Register]) * -1.0f;
} // = 0x91, // Floating Negate (FNEG [F:(4,8),REG]):16

Instruction(F1OX) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] = 1.0f / ctx->FPR_DOUBLE[Register];
	else
		ctx->FPR_SINGLE[Register] = 1.0f / ctx->FPR_SINGLE[Register];
	return;
} // = 0x92, // Floating 1/x (F1OX [F:(4,8),REG]):16

Instruction(FFCT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] = fpud_fact(ctx->FPR_DOUBLE[Register]);
	else
		ctx->FPR_SINGLE[Register] = fpus_fact(ctx->FPR_SINGLE[Register]);
	return;
} // = 0x93, // Floating Factorial (FFCT [F:(4,8),REG]):16

Instruction(FFSF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[Register] *= -1.0;
	else
		ctx->FPR_SINGLE[Register] *= -1.0f;
	return;
} // = 0x94, // Floating Flip Sign (FFSF [F:(4,8),REG]):16

Instruction(FAIF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] += ctx->GPRs[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] += ctx->GPRs[REG_HI(Register)];
	return;
} // = 0x95, // Floating Add Floating With Regular (FAIF [F:(4,4),SRC] [R:(4,4),REG]):16

Instruction(FSIF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] -= ctx->GPRs[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] -= ctx->GPRs[REG_HI(Register)];
	return;
} // = 0x96, // Floating Sub Floating With Regular (FSIF [F:(4,4),SRC] [R:(4,4),REG]):16

Instruction(FMIF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] *= ctx->GPRs[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] *= ctx->GPRs[REG_HI(Register)];
	return;
} // = 0x97, // Floating Multiply Floating With Regular (FMIF [F:(4,4),SRC] [R:(4,4),REG]):16

Instruction(FDIF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] /= (x64)ctx->GPRs[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] /= (x32)ctx->GPRs[REG_HI(Register)];
	return;
} // = 0x98, // Floating Divison Floating With Regular (FDIF [F:(4,4),SRC] [R:(4,4),REG]):16

Instruction(SFDP) {
	SET_PRECISEFLAG(ctx->sf0);
} // = 0x61, // Set Floating Double Precision (SFDP):8

Instruction(CFDP) {
	CLR_PRECISEFLAG(ctx->sf0);
} // = 0x62, // Clear Floating Double Precision (CFDP):8

Instruction(TFRX) {
	x64 BackupF;
	u64 BackupR;
	byte Register = r1();
	BackupR = ctx->GPRs[REG_HI(Register)];
	if (GET_PRECISEFLAG(ctx->sf0)) {
		BackupF = ctx->FPR_DOUBLE[REG_LO(Register)];
		ctx->FPR_DOUBLE[REG_LO(Register)] = (x64)BackupR;
	} else {
		BackupF = ctx->FPR_SINGLE[REG_LO(Register)];
		ctx->FPR_SINGLE[REG_LO(Register)] = (x32)BackupR;
	}
	ctx->GPRs[REG_HI(Register)] = (u64)BackupF;
	return;
} // = 0x63, // Exchange Floating with Regular Register (TFRX [F:(4,4),FP_REG] [R:(4,4),INT_REG]):16

Instruction(CFRI) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->GPRs[REG_HI(Register)] = ctx->FPR_DOUBLE[REG_LO(Register)];
	else
		ctx->GPRs[REG_HI(Register)] = ctx->FPR_SINGLE[REG_LO(Register)];
	return;
} // = 0x64, // Convert Floating to Regular Integer (CFRI [F:(4,4),FP_REG] [R:(4,4),INT_REG]):16

Instruction(CFFI) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_round(ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_round(ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} // = 0x65, // Convert Floating to Floating Integer (CFFI [F:(4,4),FP_REG0] [F:(4,4),FP_REG1]):16

Instruction(LSFR) {
	union {
		x32 Float;
		u32 Raw;
	}Data;
	byte Register = r1();
	Data.Raw = ctx->GPRs[REG_HI(Register)];
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = (x64)Data.Float;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = Data.Float;
	return;
} // = 0x66, // Load Single Precision Float from Register (LSFR [F:(4,4),FP_DEST] [R:(4,4),INT_SRC]):16

Instruction(LDFR) {
	union {
		x64 Float;
		u64 Raw;
	}Data;
	byte Register = r1();
	Data.Raw = ctx->GPRs[REG_HI(Register)];
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = Data.Float;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = (x32)Data.Float;
} // = 0x67, // Load Double Precision Float from Register (LSFR [F:(4,4),FP_DEST] [R:(4,4),INT_SRC]):16

Instruction(FABS) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_abs(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_abs(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x68, // Floating Absolute Value (FABS [F:(4,8),SRC]):16

Instruction(FADD) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] += ctx->FPR_DOUBLE[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] += ctx->FPR_SINGLE[REG_HI(Register)];
	return;
} // = 0x69, // Floating Addition (FADD [F:(4,4),SRC] [F:(4,4),ADDER]):16

Instruction(FSUB) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] -= ctx->FPR_DOUBLE[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] -= ctx->FPR_SINGLE[REG_HI(Register)];
	return;
} // = 0x6B, // Floating Subtraction (FSUB [F:(4,4),SRC] [F:(4,4),SUBBER]):16

Instruction(FMUL) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] *= ctx->FPR_DOUBLE[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] *= ctx->FPR_SINGLE[REG_HI(Register)];
	return;
} // = 0x6D, // Floating Multiply (FMUL [F:(4,4),SRC] [F:(4,4),FACTOR]):16

Instruction(FDIV) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] /= ctx->FPR_DOUBLE[REG_HI(Register)];
	else
		ctx->FPR_SINGLE[REG_LO(Register)] /= ctx->FPR_SINGLE[REG_HI(Register)];
	return;
} // = 0x6F, // Floating Divide (FDIV [F:(4,4),SRC] [F:(4,4),DIVISOR]):16

Instruction(FMOD) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_mod(ctx->FPR_DOUBLE[REG_HI(Register)], ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_mod(ctx->FPR_SINGLE[REG_HI(Register)], ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x71, // Floating Modulo (FMOD [F:(4,4),SRC] [F:(4,4),DIVISOR]):16

Instruction(FSIN) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_sin(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_sin(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x73, // Floating Sine{x} (FSIN [F:(4,8),SRC]):16

Instruction(FCOS) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_cos(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_cos(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x75, // Floating CoSine{x} (FCOS [F:(4,8),SRC]):16

Instruction(FTAN) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_tan(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_tan(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x77, // Floating Tangent{x} (FTAN [F:(4,8),SRC]):16

Instruction(FSEC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = 1.0 / fpud_cos(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = 1.f / fpus_cos(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x79, // Floating Secant{x} (FSEC [F:(4,8),SRC]):16

Instruction(FCSC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = 1.0 / fpud_sin(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = 1.f / fpus_sin(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x7B, // Floating CoSecant{x} (FCSC [F:(4,8),SRC]):16

Instruction(FCOT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = 1.0 / fpud_tan(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = 1.f / fpus_tan(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0xB5, // Floating CoTangent{x} (FCOT [F:(4,8),SRC]):16

Instruction(FEXP) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_pow(ctx->FPR_DOUBLE[REG_LO(Register)], ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpud_pow(ctx->FPR_SINGLE[REG_LO(Register)], ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} // = 0x7D, // Floating Exponent (FEXP [F:(4,4),BASE] [F:(4,4),EXPONENT]):16

Instruction(FAIFI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] += Immediate;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] += Immediate;
	return;
} // = 0x9A, // Floating Add Floating with Regular (FAIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80

Instruction(FSIFI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] -= Immediate;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] -= Immediate;
	return;
} // = 0x9B, // Floating Subtract Floating with Regular (FSIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80

Instruction(FMIFI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] *= Immediate;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] *= Immediate;
	return;
} // = 0x9C, // Floating Multiply Floating with Regular (FMIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80

Instruction(FDIFI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] /= Immediate;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] /= Immediate;
	return;
} // = 0x9D, // Floating Division Floating with Regular (FDIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80

Instruction(FNSIN) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_arcsin(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_arcsin(ctx->FPR_DOUBLE[REG_LO(Register)]);
	return;
} // = 0x83, // Floating Inverse Sine{x} (FNSIN [F:(4,8),SRC]):16

Instruction(FEXPT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = fpud_pow(ctx->FPR_DOUBLE[REG_HI(Register0)], ctx->FPR_DOUBLE[REG_LO(Register0)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = fpus_pow(ctx->FPR_SINGLE[REG_HI(Register0)], ctx->FPR_SINGLE[REG_LO(Register0)]);
	return;
} // = 0x80, // Floating Exponent To (FEXPT [F:(4,4),BASE] [F:(4,4),EXPONENT] [F:(4,8),DEST]):24

Instruction(FEXPI) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Registers)] = fpud_expi(ctx->GPRs[REG_HI(Registers)], ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_LO(Registers)] = fpus_expi(ctx->GPRs[REG_HI(Registers)], ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x7E, // Floating Exponent Integer (FEXPI [F:(4,4),BASE] [R:(4,4),EXPONENT]):16

Instruction(FCOTT) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_cot(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_cot(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0xB6, // Floating CoTangent{x} To (FCOTT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FCSCT) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_csc(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_csc(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x7C, // Floating CoSecant{x} To (FCSCT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FCOST) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_cos(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_cos(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x76, // Floating CoSine{x} To (FCOST [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FSECT) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_sec(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_sec(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x7A, // Floating Secant{x} To (FSECT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FTANT) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_tan(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_tan(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x78, // Floating Tangnet{x} To (FTANT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FMULT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = ctx->FPR_DOUBLE[REG_LO(Register0)] * ctx->FPR_DOUBLE[REG_HI(Register1)];
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = ctx->FPR_SINGLE[REG_LO(Register0)] * ctx->FPR_SINGLE[REG_HI(Register1)];
	return;
} // = 0x6E, // Floating Multiply To (FMULT [F:(4,4),SRC] [F:(4,4),FACTOR] [F:(4,8),DEST]):24

Instruction(FADDT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = ctx->FPR_DOUBLE[REG_LO(Register0)] + ctx->FPR_DOUBLE[REG_HI(Register1)];
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = ctx->FPR_SINGLE[REG_LO(Register0)] + ctx->FPR_SINGLE[REG_HI(Register1)];
	return;
} // = 0x6A, // Floating Addition To (FADDT [F:(4,4),SRC] [F:(4,4),ADDER] [F:(4,8),DST]):24

Instruction(FSUBT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = ctx->FPR_DOUBLE[REG_LO(Register0)] - ctx->FPR_DOUBLE[REG_HI(Register1)];
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = ctx->FPR_SINGLE[REG_LO(Register0)] - ctx->FPR_SINGLE[REG_HI(Register1)];
	return;
} // = 0x6C, // Floating Subtraction To (FSUBT [F:(4,4),SRC] [F:(4,4),SUBBER], [F:(4,8),DEST]):24

Instruction(FDIVT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = ctx->FPR_DOUBLE[REG_LO(Register0)] / ctx->FPR_DOUBLE[REG_HI(Register1)];
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = ctx->FPR_SINGLE[REG_LO(Register0)] / ctx->FPR_SINGLE[REG_HI(Register1)];
	return;
} // = 0x70, // Floating Divide To (FDIVT [F:(4,4),SRC] [F:(4,4),DIVISOR] [F:(4,8),DEST]):24

Instruction(FMODT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = fpud_mod(ctx->FPR_DOUBLE[REG_HI(Register0)], ctx->FPR_DOUBLE[REG_LO(Register0)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = fpus_mod(ctx->FPR_SINGLE[REG_HI(Register0)], ctx->FPR_SINGLE[REG_LO(Register0)]);
	return;

} // = 0x72, // Floating Modulo To (FMODT [F:(4,4),SRC] [F:(4,4),DIVISOR] [F:(4,8),DEST]):24

Instruction(FSINT) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Registers)] = fpud_sin(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_HI(Registers)] = fpus_sin(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x74, // Floating Sine{x} To (FSINT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNCOS) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Registers)] = fpud_arccos(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_LO(Registers)] = fpus_arccos(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x85, // Floating Inverse CoSine{x} (FNCOS [F:(4,8),SRC]):16

Instruction(FNTAN) {
	byte Registers = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Registers)] = fpud_arctan(ctx->FPR_DOUBLE[REG_LO(Registers)]);
	else
		ctx->FPR_SINGLE[REG_LO(Registers)] = fpus_arctan(ctx->FPR_SINGLE[REG_LO(Registers)]);
	return;
} // = 0x87, // Floating Inverse Tangent{x} (FNTAN [F:(4,8),SRC]):16

Instruction(FNSEC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_arcsec(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_arcsec(ctx->FPR_DOUBLE[REG_LO(Register)]);
	return;
} // = 0x89, // Floating Inverse Secant{x} (FNSEC [F:(4,8),SRC]):16

Instruction(FNCSC) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_arccsc(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_arccsc(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x8A, // Floating Inverse CoSecant{x} (FNCSC [F:(4,8),SRC]):16

Instruction(FNCOT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_arccot(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_arccot(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // = 0x8B, // Floating Inverse CoTangent{x} (FNCOT [F:(4,8),SRC]):16

Instruction(FABST) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_abs(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_abs(ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} // = 0xB7, // Floating Absolute Value To (FABS [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(GFCPS) {
	byte Register = r1();
	ctx->GPRs[Register] = ctx->sf1;
} // = 0x60, // Get Floating CoProcessor Status (GFCPS [R:(4,8),DEST]):16


Instruction(FNSINT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arcsin(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_arcsin(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x84, // Floating Inverse Sine{x} To (FNSINT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNCOST) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arccos(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_arccos(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x86, // Floating Inverse CoSine{x} To (FNCOST [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNTANT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arctan(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_arctan(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x88, // Floating Inverse Tangent{x} To (FNTANT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNSECT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arcsec(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_sin(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x8C, // Floating Inverse Secant{x} To (FNSECT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNCSCT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arccsc(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_arccsc(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x8D, // Floating Inverse CoSecant{x} To (FNCSCT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FNCOTT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Register)] = fpud_arccot(ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_HI(Register)] = fpus_arccot(ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x8E, // Floating Inverse CoTangent{x} To (FNCOTT [F:(4,4),SRC] [F:(4,4),DEST]):16

Instruction(FMODIF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_mod(ctx->GPRs[REG_HI(Register)], ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_mod(ctx->FPRs[REG_HI(Register)], ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x99, // Floating Modulo Floating With Regular (FMODIF [F:(4,4),SRC] [R:(4,4),REG]):16

Instruction(FEXPII) {
	byte Register = r1();
	u16 Exponenet = rx(2);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_pow(Exponenet, ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_pow(Exponenet, ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} //  = 0x7F, // Floating Exponent Immediate Integer (FEXPII [F:(4,8),BASE] [I:(16,16),EXPONENT]):32

Instruction(FEXPIT) {
	byte Register0 = r1();
	byte Register1 = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = fpud_pow(ctx->GPRs[REG_HI(Register0)], ctx->FPR_DOUBLE[REG_LO(Register0)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = fpus_pow(ctx->GPRs[REG_HI(Register0)], ctx->FPR_SINGLE[REG_LO(Register0)]);
	return;
} //  = 0x81, // Floating Exponent Integer To (FEXPIT [F:(4,4),BASE] [R:(4,4),EXPONENT] [F:(4,8),DEST]):24

Instruction(FMODIFI) {
	byte Register0 = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register0)] = fpud_mod(ctx->FPR_DOUBLE[REG_LO(Register0)], Immediate);
	else
		ctx->FPR_SINGLE[REG_LO(Register0)] = fpus_mod(ctx->FPR_SINGLE[REG_LO(Register0)], Immediate);
	return;
} // Floating Modulo Floating with Regular (FMODIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80

Instruction(FEXPIIT) {
	byte Register0 = r1();
	u16 Immediate = rx(2);
	byte Register1 = r1();

	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register1)] = fpud_pow(Immediate, ctx->FPR_DOUBLE[REG_LO(Register0)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register1)] = fpus_pow(Immediate, ctx->FPR_SINGLE[REG_LO(Register0)]);
	return;
} // Floating Exponent Immediate To Integer (FEXPIIT [F:(4,8),BASE] [I:(16,16),EXPONENT] [F:(4,8),DEST]):40

Instruction(FLOG2) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_log2(ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_log2(ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
}//  = 0x9F, // Floating Log2{x} (FLOG2 [F:(4,4),SRC] [F:(4,4),VAL]):16

Instruction(FLOG10) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_logx(10, ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_logx(10, ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} // = 0xA0, // Floating Log10{x} (FLOG10 [F:(4,4),SRC] [F:(4,4),VAL]):16

Instruction(FLOGE) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_ln(ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_ln(ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} //= 0xA1, // Floating Ln{x} (FLOGE [F:(4,4),SRC] [F:(4,4),VAL]):16

Instruction(FE10X) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_pow(ctx->FPR_DOUBLE[REG_HI(Register)], 10);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_pow(ctx->FPR_SINGLE[REG_HI(Register)], 10);
	return;
} //= 0xA2, // Floating 10^x (FE10X [F:(4,4),SRC] [F:(4,4),VAL]):16

Instruction(FNOP) {
	return;
} // 0xA3, // Floating No Operation (FNOP):8

Instruction(F2XM1) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_pow(2, ctx->FPR_DOUBLE[REG_HI(Register)]) - 1;
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_pow(2, ctx->FPR_SINGLE[REG_HI(Register)]) - 1;
	return;
} //= 0xA4, // Floating {2^x}-1 (F2XM1 [F:(4,4),SRC] [F:(4,4),VAL]):16

Instruction(FCMPFR) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0)) {
		if (ctx->FPR_DOUBLE[REG_LO(Register)] > ctx->GPRs[REG_HI(Register)])
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_DOUBLE[REG_LO(Register)] == ctx->GPRs[REG_HI(Register)])
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	} else {
		if (ctx->FPR_SINGLE[REG_LO(Register)] > ctx->GPRs[REG_HI(Register)])
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_SINGLE[REG_LO(Register)] == ctx->GPRs[REG_HI(Register)])
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
} // = 0xA5, // Floating Compare Float Regular (FCMPFR [F:(4,4),VAL0] [R:(4,4),VAL1]):16

Instruction(FCMPFF) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0)) {
		if (ctx->FPR_DOUBLE[REG_LO(Register)] > ctx->FPR_DOUBLE[REG_HI(Register)])
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_DOUBLE[REG_LO(Register)] == ctx->FPR_DOUBLE[REG_HI(Register)])
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
	else {
		if (ctx->FPR_SINGLE[REG_LO(Register)] > ctx->FPR_SINGLE[REG_HI(Register)])
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_SINGLE[REG_LO(Register)] == ctx->FPR_SINGLE[REG_HI(Register)])
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
} // = 0xA6, // Floating Compare Float Float (FCMPFF [F:(4,4),VAL0] [F:(4,4),VAL1]):16

Instruction(FCMPFRI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0)) {
		if (ctx->FPR_DOUBLE[REG_LO(Register)] > Immediate)
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_DOUBLE[REG_LO(Register)] == Immediate)
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
	else {
		if (ctx->FPR_SINGLE[REG_LO(Register)] > Immediate)
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_SINGLE[REG_LO(Register)] == Immediate)
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
} // = 0xA7, // Floating Compare Float Regular{Imm} (FCMPFRI [F:(4,8),VAL0] [I:(64,64),VAL1]):80

Instruction(FCMPFFI) {
	byte Register = r1();
	union {
		x64 Float;
		u64 Int;
	}FloatData;
	FloatData.Int = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0)) {
		if (ctx->FPR_DOUBLE[REG_LO(Register)] > FloatData.Float)
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_DOUBLE[REG_LO(Register)] == FloatData.Float)
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
	else {
		if (ctx->FPR_SINGLE[REG_LO(Register)] > FloatData.Float)
			SET_GREATFLAG(ctx->sf0);
		else
			SET_LESSFLAG(ctx->sf0);
		if (ctx->FPR_SINGLE[REG_LO(Register)] == FloatData.Float)
			SET_EQUALFLAG(ctx->sf0);
		else
			CLR_EQUALFLAG(ctx->sf0);
	}
} // = 0xA8, // Floating Compare Float Float{Imm} (FCMPFFI [F:(4,8),VAL0] [I:(64,64),VAL1]):80

Instruction(FEEX) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_pow(ctx->FPR_DOUBLE[REG_HI(Register)], _FPU_E);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_pow(ctx->FPR_SINGLE[REG_HI(Register)], _FPU_E);
	return;
} //0xA9, // Floating e^x (FEEX [F:(4,8),SRC]):16

Instruction(CFFT) {
	ctx->sf0 = ctx->sf1;
} //0xAA, // Copy Floating Flags to System Flags (CFFT):8

Instruction(FSQRT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_rooti(2, ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_rooti(2, ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // 0xAB, // Floating square root (FSQRT [F:(4,8),SRC]):16

Instruction(FCBRT) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_rooti(3, ctx->FPR_DOUBLE[REG_LO(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_rooti(3, ctx->FPR_SINGLE[REG_LO(Register)]);
	return;
} // 0xAC, // Floating cubic root (FCBRT [F:(4,8),SRC]):16

Instruction(FNRTI) {
	byte Data = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_HI(Data)] = fpud_rooti(REG_LO(Data), ctx->FPR_DOUBLE[REG_HI(Data)]);
	else
		ctx->FPR_SINGLE[REG_HI(Data)] = fpus_rooti(REG_LO(Data), ctx->FPR_SINGLE[REG_HI(Data)]);
} // 0xAD, // Floating nth-root (FNRT [I:(4,4),ROOT] [F:(4,4),SRC]):16

Instruction(FLOG2I) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_log2(Immediate);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_log2(Immediate);
	return;
} //= 0xAE, // Floating Log2{x}{Imm} (FLOG2I [F:(4,8),DEST] [I:(64,64),VALUE]):80

Instruction(FLOG10I) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_logx(10, Immediate);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_logx(10, Immediate);
	return;
} // = 0xAF, // Floating Log10{x}{Imm} (FLOG10I [F:(4,8),DEST] [I:(64,64),VALUE]):80

Instruction(FLOGEI) {
	byte Register = r1();
	u64 Immediate = rx(8);
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_ln(Immediate);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_ln(Immediate);
	return;
} //= 0xB0, // Floating Ln{x}{Imm} (FLOGEI [F:(4,8),DEST] [I:(64,64),VALUE]):80

Instruction(FLOG2R) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_log2(ctx->GPRs[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_log2(ctx->GPRs[REG_HI(Register)]);
	return;
} //= 0xB1, // Floating Log2{x} with Regular (FLOG2R [F:(4,4),DEST] [R:(4,4),VALUE]):16

Instruction(FLOG10R) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_logx(10, ctx->GPRs[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_logx(10, ctx->GPRs[REG_LO(Register)]);
	return;
} // = 0xB2, // Floating Log10{x} with Regular (FLOG10R [F:(4,4),DEST] [R:(4,4),VALUE]):16

Instruction(FLOGER) {
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_ln(ctx->GPRs[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_ln(ctx->GPRs[REG_LO(Register)]);
	return;
} //= 0xB3, // Floating Ln{x} with Regular (FLOGER [F:(4,4),DEST] [R:(4,4),VALUE]):16

Instruction(FNRTX) {
	u32 Immediate = rx(4);
	byte Register = r1();
	if (GET_PRECISEFLAG(ctx->sf0))
		ctx->FPR_DOUBLE[REG_LO(Register)] = fpud_rooti(Immediate, ctx->FPR_DOUBLE[REG_HI(Register)]);
	else
		ctx->FPR_SINGLE[REG_LO(Register)] = fpus_rooti(Immediate, ctx->FPR_SINGLE[REG_HI(Register)]);
	return;
} // 0xB4, // Floating nth-root with large root (FNRTX [I:(32,32),ROOT] [F:(4,8),SRC]):48

Instruction(CPUFQ) {

} // = 0xB8, // CPU Feature Query (CPUFQ [R:(4,4),FEATURE] [R:(4,4),DEST]):16

Instruction(CPUFS) {

} //  = 0xB9, // CPU Feature Set {Enabled} (CPUFQ [R:(4,8),FEATURE]):16

Instruction(CPUFC) {

} // = 0xBA, // CPU Feature Clear {Disabled} (CPUFQ [R:(4,8),FEATURE]):16

Instruction(CPUFDB) {

} // = 0xBB, // CPU Feature SendData Byte (CPUFDB [R:(4,4),FEATURE] [R:(4,4),DATA]):16

Instruction(CPUFDQ) {

} // = 0xBC, // CPU Feature SendData QuarterWord (CPUFDQ [R:(4,4),FEATURE] [R:(4,4),DATA]):16

Instruction(CPUFDH) {

} // = 0xBD, // CPU Feature SendData HalfWord (CPUFDH [R:(4,4),FEATURE] [R:(4,4),DATA]):16

Instruction(CPUFDW) {

} // = 0xBE, // CPU Feature SendData Word (CPUFDW [R:(4,4),FEATURE] [R:(4,4),DATA]):16

Instruction(CPUFRB) {

} // = 0xBF, // CPU Feature RecvData Byte (CPUFRB [R:(4,4),FEATURE] [R:(4,4),DEST]):16

Instruction(CPUFRQ) {

} // = 0xC0, // CPU Feature RecvData QuarterWord (CPUFRQ [R:(4,4),FEATURE] [R:(4,4),DEST]):16

Instruction(CPUFRH) {

} // = 0xC1, // CPU Feature RecvData HalfWord (CPUFRH [R:(4,4),FEATURE] [R:(4,4),DEST]):16

Instruction(CPUFRW) {

} // = 0xC2, // CPU Feature RecvData Word (CPUFRW [R:(4,4),FEATURE] [R:(4,4),DEST]):16