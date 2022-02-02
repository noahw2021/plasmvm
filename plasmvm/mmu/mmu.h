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

#define _ACCESS_READ	0x01	
#define _ACCESS_WRITE	0x02
#define _ACCESS_EXEC	0x04

void mmu_init(void);
void mmu_shutdown(void);
void mmu_clock(void);
word mmu_translate(u64 Virtual, byte AccessFlags);

#endif /* mmu_h */
