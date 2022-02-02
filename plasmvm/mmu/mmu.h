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
byte rx(byte Count);

#define _ACCESS_READ	0x01	
#define _ACCESS_WRITE
#define _ACCESS_EXEC

void mmu_init(void);
void mmu_clock(void);
word mmu_translate(u64 Physical, byte AccessFlags);

#endif /* mmu_h */
