//
//  cpu_advops.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "cpu.h"
#include "../mmu/mmu.h"
// Common operations that may change in the future

void cpui_fireint(byte Interrupt) {
	if (GET_INTFLAG(ctx->sf0))
		cpui_enter(ctx->InterruptHandlers[Interrupt]);
}

void cpui_go(word Address) {
	ctx->ip = mmu_translatevm(Address, _ACCESS_READ | _ACCESS_EXEC);
}

void cpui_enter(word Address) {
	mmui_stackput(ctx->ip);
	ctx->ip = mmu_translatevm(Address, _ACCESS_READ | _ACCESS_EXEC);
}

void cpui_return(void) {
	ctx->ip = mmui_stackpull();
}

void cpui_pushall(void) {
	for (int i = 0; i < _REGISTERCNT; i++)
		mmui_stackput(ctx->Registers[i]);
}

void cpui_pushgen(void) {
	for (int i = 0; i < _GPRCNT; i++)
		mmui_stackput(ctx->GPRs[i]);
}

void cpui_pullall(void) {
	for (int i = 0; i< _REGISTERCNT; i++)
		ctx->Registers[i] = mmui_stackpull();
}

void cpui_pullgen(void) {
	for (int i = 0; i< _GPRCNT; i++)
		ctx->Registers[i] = mmui_stackpull();
}
