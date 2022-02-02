//
//  read.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "mmu.h"

byte r1(void) {
	byte* VirtualRam = (byte*)mmu_translate(ctx->ip, _ACCESS_READ);
	return VirtualRam[++ctx->ip];
}
word rx(byte Count) {
	word Return = 0;
	
	while (Count) {
		Return |= r1();
		Return <<= 8;
		Count--;
	}
	return Return;
}
