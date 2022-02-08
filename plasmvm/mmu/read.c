//
//  read.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "mmu.h"

byte r1(void) {
	byte* VirtualRam = (byte*)mmu_translate(ctx->ip, _ACCESS_READ);
	byte Return = VirtualRam[0];
	ctx->ip++;
	return Return;
}

u64 Masks[8] = {
	0x00000000000000FF,
	0x000000000000FFFF,
	0x0000000000FFFFFF,
	0x00000000FFFFFFFF,
	0x000000FFFFFFFFFF,
	0x0000FFFFFFFFFFFF,
	0x00FFFFFFFFFFFFFF,
	0xFFFFFFFFFFFFFFFF
};

word rx(byte Count) {
	word* VirtualRam = (word*)mmu_translate(ctx->ip, _ACCESS_READ);
	word Return = VirtualRam[0];
	Return &= Masks[Count - 1];
	ctx->ip += Count;
	return Return;
}
