//
//  cpu_engine.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "cpu.h"
#include "features/cpuf.h"
#include "../mmu/mmu.h"
#include "../io/io.h"
#include "../io/term/term.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int GlobalArgc;
extern char** GlobalArgv;
extern int main(int, char**);

void cpu_init(void) {
	ctx = malloc(sizeof(ictx_t));
	memset(ctx, 0, sizeof(ictx_t));

	cpuf_init();
	return;
}
void cpu_clock(void) {
	ctx->HighResolutionTimer++;
	clock_t Timer, Timer2;
	if (cpuf->Flags.Active)
		Timer = clock();
	
	if (!cpuf->Flags.Skip) {
		byte Opcode = r1();
		cpu_opcode(Opcode);
	}
	
	if (cpuf->Flags.Active)
		Timer2 = clock();

	if (cpuf->Flags.Active) {
		clock_t Difference = Timer2 - Timer;
		x64 ClocksToMs = Difference / CLOCKS_PER_SEC;
		if (cpuf->Flags.Wait) {
			if (cpuf->TimerMs > ClocksToMs)
				cpuf->TimerMs -= ClocksToMs;
			else
				cpui_fireint(cpuf->Interrupt);
		}
		if (cpuf->Flags.Repeat) {
			if (cpuf->LocalOffset == 0)
				cpuf->LocalOffset = cpuf->TimerMs;
			if (cpuf->LocalOffset > ClocksToMs) {
				cpuf->LocalOffset -= ClocksToMs;
			} else {
				cpui_fireint(cpuf->Interrupt);
				cpuf->LocalOffset = cpuf->TimerMs;
			}
		}
	}
	
	if (cpuf->Flags.PowerActive) {
		if (cpuf->Flags.PowerShuttingDown) {
			cpuf->PowerTimerTargetTicks--;
			if (cpuf->PowerTimerTargetTicks == 0) {
				SET_HALTFLAG(ctx->sf0);
				CLR_INTFLAG(ctx->sf0);
			}
			if (cpuf->Flags.Restarting) {
				mmu_shutdown();
				io_shutdown();
				cpu_shutdown();
				main(GlobalArgc, GlobalArgv); // recursion
			}
		}
		if (cpuf->Flags.Sleeping) {
			cpuf->Flags.Asleep = 1;
			cpuf->Flags.Sleeping = 0;
			termi_black();
		}
	}
}
void cpu_opcode(byte Opcode) {
	InstructionHandlers[Opcode]();
}
void cpu_shutdown(void) {
	free(ctx);
	cpuf_shutdown();
}
