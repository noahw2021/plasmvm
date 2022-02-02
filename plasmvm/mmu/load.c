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
		printf("[ERR]: Failed to open BIOS image '%s'.\n", vmctx->BiosString);
		vmctx->Error = _ERROR_INVALIDFILE;
		return;
	}
	fseek(BiosImage, 0, SEEK_END);
	u32 BiosImageSize = ftell(BiosImage);
	fseek(BiosImage, 0, SEEK_SET);
	
	if (BiosImageSize > 65535) {
		printf("[WARN]: The specified BIOS is larger than 64KB.\n");
	}
	
	void* PhysicalBios = malloc(BiosImageSize);
	fread(PhysicalBios, BiosImageSize, 1, BiosImage);
	fclose(BiosImage);
	
	memcpy(vmctx->PhysicalRam, PhysicalBios, BiosImageSize);
	ctx->ip = 0x00;
	
	if (vmctx->Flags.RamdiskPresent) {
		
	}
}
void mmu_shutdown(void) {
	
}
void mmu_clock(void) {
	
}
