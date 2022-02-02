//
//  mmu.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "mmu.h"
#include "../ctx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void mmu_init(void) {
	vmctx->PhysicalRam = malloc(vmctx->PhysicalMemory);
	memset(vmctx->PhysicalRam, 0, vmctx->PhysicalMemory);
	
	FILE* BiosImage = fopen(vmctx->BiosString, "rb");
	if (!BiosImage) {
		printf("[ERR]: Failed to open ")
	}
}
void mmu_shutdown(void) {
	
}
void mmu_clock(void) {
	
}
