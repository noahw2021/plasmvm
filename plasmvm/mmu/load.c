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
	
	free(PhysicalBios);
	
	if (vmctx->Flags.RamdiskPresent) {
		FILE* RamdiskImage = fopen(vmctx->RamdiskString, "rb");
		if (!RamdiskImage) {
			printf("[ERR]: Failed to open ramdisk image '%s'.\n", vmctx->RamdiskString);
			vmctx->Error = _ERROR_INVALIDFILE;
			return;
		}
		fseek(RamdiskImage, 0, SEEK_END);
		u32 RamdiskImageSize = ftell(RamdiskImage);
		fseek(RamdiskImage, 0, SEEK_SET);
		
		if (RamdiskImageSize > vmctx->PhysicalMemory) {
			printf("[WARN]: The ramdisk image loaded is larger than available physical memory.\n");
		}
		
		void* Ramdisk = malloc(RamdiskImageSize);
		fread(Ramdisk, RamdiskImageSize, 1, RamdiskImage);
		fclose(RamdiskImage);
		
		memcpy(vmctx->PhysicalRam, Ramdisk, RamdiskImageSize % vmctx->PhysicalMemory);
		free(Ramdisk);
	}
}
void mmu_shutdown(void) {
	free(vmctx->PhysicalRam);
}
void mmu_clock(void) {
	
	return; // not much to do here yet, maybe mmio?
}
