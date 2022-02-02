//
//  main.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#include "ctx.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"

ictx_t* ctx;
vmctx_t* vmctx;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	vmctx = malloc(sizeof(vmctx_t));
	memset(vmctx, 0, sizeof(vmctx_t));
	
	vmctx->PhysicalMemory = 16777216;
	for (int i = 0; i < argc; i++) {
		if (strstr(argv[i], "-h")) {
			printf("PLASMvm Emulator\n\n");
			printf("Configuration:\n");
			printf("-m: Memory amount, ends in kb, mb, gb, or no suffix.\n");
			printf("-d: Disk image, should be raw.\n");
			printf("-r: Ramdisk image, loaded into physical memory from file.\n");
			printf("-b: BIOS image, mapped to 0x100 and executed.\n\n");
			printf("Switches:\n");
			printf("-h: Shows this menu.\n\n");
			printf("Example:\n");
			printf("%s -b=bios.img -m=16mb -d=disk.img\n", argv[0]);
			return 0;
		}
		if (strstr(argv[i], "-m=")) {
			if (strstr(argv[i], "mb")) {
				char* Copy = malloc(128);
				strcpy(Copy, argv[i] + 3); // account for -m=
				strstr(Copy, "mb")[0] = 0x00;
				vmctx->PhysicalMemory = strtoull(Copy, NULL, 10) * (1 << 20);
				free(Copy);
			} else
			if (strstr(argv[i], "kb")) {
				char* Copy = malloc(128);
				strcpy(Copy, argv[i] + 3);
				strstr(Copy, "kb")[0] = 0x00;
				vmctx->PhysicalMemory = strtoull(Copy, NULL, 10) * (1 << 12);
				free(Copy);
			} else
			if (strstr(argv[i], "gb")) {
				char* Copy = malloc(128);
				strcpy(Copy, argv[i] + 3);
				strstr(Copy, "gb")[0] = 0x00;
				vmctx->PhysicalMemory = strtoull(Copy, NULL, 10) * (1 << 30);
				free(Copy);
			} else {
				vmctx->PhysicalMemory = strtoull(argv[i] + 3, NULL, 10);
			}
		}
		
		if (strstr(argv[i], "-d=")) {
			vmctx->HddString = malloc(241);
			strcpy(vmctx->HddString, argv[i] + 3);
			vmctx->Flags.HddPresent = 1;
		}
		if (strstr(argv[i], "-r=")) {
			vmctx->HddString = malloc(241);
			strcpy(vmctx->RamdiskString, argv[i] + 3);
			vmctx->Flags.RamdiskString = 1;
		}
		if (strstr(argv[i], "-b=")) {
			vmctx->HddString = malloc(241);
			strcpy(vmctx->BiosString, argv[i] + 3);
			vmctx->Flags.BiosPresent = 1;
		}
	}
	
	if (!vmctx->Flags.BiosPresent) {
		printf("[ERR]: No BIOS Present!\n");
		if (vmctx->Flags.RamdiskString)
			free(vmctx->RamdiskString);
		if (vmctx->Flags.HddPresent)
			free(vmctx->HddString);
		free(vmctx);
		return 0;
	}
	
	cpu_init();
	mmu_init();
	
	while (1) {
		mmu_clock();
		cpu_clock();
		
		
	}
}
