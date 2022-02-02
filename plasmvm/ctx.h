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
}vmctx_t;

extern vmctx_t* vmctx;
extern ictx_t* ctx;

#endif /* ctx_h */
