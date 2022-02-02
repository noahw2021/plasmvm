//
//  ctx.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef ctx_h
#define ctx_h

typedef unsigned char byte;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64, word;

typedef char i8, str;
typedef short i16;
typedef long i32;
typedef long long i64;

#define FLAG_TF 0x0001 // Trap Flag
#define FLAG_IF	0x0002 // Interupt Flag
#define FLAG_HF	0x0004 // Halt Flag
#define FLAG_GF	0x0008 // Greater Flag
#define FLAG_LF 0x0010 // Less Flag
#define FLAG_EF 0x0020 // Equal Flag
#define FLAG_ZF 0x0040 // Zero Flag
#define FLAG_CF 0x0080 // Carry Flag
#define FLAG_UF	0x0100 // User Flag
#define FLAG_SF 0x0200 // System Flag
#define FLAG_XF	0x0400 // Interrupt Input Flag

#define GET_TRAPFLAG(x)		(x & FLAG_TF)
#define GET_INTFLAG(x)		(x & FLAG_IF)
#define GET_HALTFLAG(x)		(x & FLAG_HF)
#define GET_GREATFLAG(x)	(x & FLAG_GF)
#define GET_LESSFLAG(x)		(x & FLAG_LF)
#define GET_EQUALFLAG(x)	(x & FLAG_EF)
#define GET_ZEROFLAG(x)		(x & FLAG_ZF)
#define GET_CARRYFLAG(x)	(x & FLAG_CF)
#define GET_USERFLAG(x)		(x & FLAG_UF)
#define GET_SYSTEMFLAG(x)	(x & FLAG_SF)
#define GET_INPUTFLAG(x) 	(x & FLAG_XF)

#define SET_TRAPFLAG(x)		(x |= FLAG_TF)
#define SET_INTFLAG(x)		(x |= FLAG_IF)
#define SET_HALTFLAG(x)		(x |= FLAG_HF)
#define SET_GREATFLAG(x)	(x |= FLAG_GF)
#define SET_LESSFLAG(x)		(x |= FLAG_LF)
#define SET_EQUALFLAG(x)	(x |= FLAG_EF)
#define SET_ZEROFLAG(x)		(x |= FLAG_ZF)
#define SET_CARRYFLAG(x)	(x |= FLAG_CF)
#define SET_USERFLAG(x)		(x |= FLAG_UF)
#define SET_SYSTEMFLAG(x)	(x |= FLAG_SF)
#define SET_INPUTFLAG(x) 	(x |= FLAG_XF)

#define CLR_TRAPFLAG(x)		(x &= FLAG_TF)
#define CLR_INTFLAG(x)		(x &= FLAG_IF)
#define CLR_HALTFLAG(x)		(x &= FLAG_HF)
#define CLR_GREATFLAG(x)	(x &= FLAG_GF)
#define CLR_LESSFLAG(x)		(x &= FLAG_LF)
#define CLR_EQUALFLAG(x)	(x &= FLAG_EF)
#define CLR_ZEROFLAG(x)		(x &= FLAG_ZF)
#define CLR_CARRYFLAG(x)	(x &= FLAG_CF)
#define CLR_USERFLAG(x)		(x &= FLAG_UF)
#define CLR_SYSTEMFLAG(x)	(x &= FLAG_SF)
#define CLR_INPUTFLAG(x) 	(x &= FLAG_XF)

typedef struct ictx {
	union {
		u64 Registers[24];
		struct {
			// General Purpose Registers
			u64 r0,  r1,  r2,  r3;
			u64 r4,  r5,  r6,  r7;
			u64 r8,  r9,  r10, r11;
			u64 r12, r13, r14, r15;
			
			// System State Registers
			u64 ip; // Instruction Pointer
			u64 sp; // Stack Pointer
			
			// System Control Registers
			u64 sd0, sd1; // System Descriptor
			u64 vm0, vm1; // Virtual Memory Descriptor
			
			// Program Control Registers
			u64 sf0, sf1; // System Flags
		};
	};
}ictx_t;

#define _SUCCESS		   0x10000000
#define _ERROR			   0x20000000
#define _ERROR_INVALIDFILE 0x20000001

typedef struct vmctx {
	u64 PhysicalMemory;
	char* HddString;
	char* BiosString;
	char* RamdiskString;
	union {
		u64 Raw;
		struct {
			byte HddPresent;
			byte BiosPresent;
			byte RamdiskString;
		};
	}Flags;
	void* PhysicalRam;
	u32 Error;
}vmctx_t;

extern vmctx_t* vmctx;
extern ictx_t* ctx;

#endif /* ctx_h */
