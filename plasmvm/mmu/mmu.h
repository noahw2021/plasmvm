//
//  mmu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef mmu_h
#define mmu_h
#include "../ctx.h"

byte r1(void);
word rx(byte Count);

word mmui_stackpull(void);
byte mmui_stackpullbyte(void);

void mmui_stackput(word Value);
void mmui_stackputbyte(byte Value);

#define _ACCESS_READ	0x01	
#define _ACCESS_WRITE	0x02
#define _ACCESS_EXEC	0x04

void mmu_init(void);
void mmu_shutdown(void);
void mmu_clock(void);
void* mmu_translate(u64 Virtual, byte AccessFlags);

// Virtual Memory Descriptor Sections

// Bit Locations

// VMD0 written in PLANG structure notation
/*
 STRUCT plang:
	00, 01, Enabled
	01, 32, PageCount
	31, 33, Reserved
 END;
 */

#define VMD0_GET_ENABLED(x)  ((x & 0x0000000000000001) >> 00)
#define VMD0_GET_PAGECNT(x)  ((x & 0x00000001FFFFFFFE) >> 01)
#define VMD0_GET_RESERVED(x) ((x & 0xFFFFFFFE00000000) >> 33)

#define VMD0_SET_ENABLED(x, v)  (x &= 0xFFFFFFFFFFFFFFFE); (x |= (v & 0x0000000000000001) >> 00)
#define VMD0_SET_PAGECNT(x, v)  (x &= 0xFFFFFFFE00000001); (x |= (v & 0x00000001FFFFFFFE) >> 01)
#define VMD0_SET_RESERVED(x, v) (x &= 0x00000001FFFFFFFF); (x |= (v & 0xFFFFFFFE00000000) >> 33)

#define VMD1_GET_ADDRESS(x) ((x & 0xFFFFFFFFFFFFFFFF) >> 0)

#define VMD1_SET_ADDRESS(x, v) (x &= 0x0000000000000000); (x |= (v & 0xFFFFFFFFFFFFFFFF) >> 0)

#endif /* mmu_h */
