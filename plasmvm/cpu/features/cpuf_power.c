//
//  cpuf_power.c
//  plasmvm
//
//  Created by Noah Wooten on 3/23/22.
//
#include "cpuf.h"
#include "../../mmu/mmu.h"
#include "../cpu.h"

void cpuf_power_set(void) {
	cpuf->Flags.PowerActive = 1;
}
void cpuf_power_clear(void) {
	cpuf->Flags.PowerActive = 0;
}
void cpuf_power_shutdown(void) {
	if (!cpuf->Flags.PowerActive || !cpuf->Flags.HasPowerInterrupt) {
		CLR_INTFLAG(ctx->sf0);
		SET_HALTFLAG(ctx->sf0);
		return;
	} else {
		if (cpuf->Flags.PowerShuttingDown) {
			cpuf->PowerBackupTimer = ctx->HighResolutionTimer;
			cpuf->PowerTimerTargetTicks = 5000;
			mmui_stackput(CPUFPWR_DATA_SHUTTINGDOWN5000TICKS);
			cpui_fireint(cpuf->PowerInterrupt);
		}
		else {
			cpuf->PowerBackupTimer = ctx->HighResolutionTimer;
			cpuf->PowerTimerTargetTicks = 500000;
			mmui_stackput(CPUFPWR_DATA_SHUTTINGDOWN500000TICKS);
			cpui_fireint(cpuf->PowerInterrupt);
			cpuf->Flags.PowerShuttingDown = 1;
			cpuf->Flags.Restarting = 0;
		}
	}
}
void cpuf_power_sleep(void) {
	if (!cpuf->Flags.PowerActive) {
		return;
	} else {
		mmui_stackput(CPUFPWR_DATA_SLEEP);
		cpui_fireint(cpuf->PowerInterrupt);
		cpuf->Flags.Sleeping = 1;
	}
}
void cpuf_power_restart(void) {
	if (!cpuf->Flags.PowerActive || !cpuf->Flags.HasPowerInterrupt) {
		CLR_INTFLAG(ctx->sf0);
		SET_HALTFLAG(ctx->sf0);
		return;
	} else {
		if (cpuf->Flags.PowerShuttingDown) {
			cpuf->PowerBackupTimer = ctx->HighResolutionTimer;
			cpuf->PowerTimerTargetTicks = 5000;
			mmui_stackput(CPUFPWR_DATA_SHUTTINGDOWN5000TICKS);
			cpui_fireint(cpuf->PowerInterrupt);
		}
		else {
			cpuf->PowerBackupTimer = ctx->HighResolutionTimer;
			cpuf->PowerTimerTargetTicks = 500000;
			mmui_stackput(CPUFPWR_DATA_SHUTTINGDOWN500000TICKS);
			cpui_fireint(cpuf->PowerInterrupt);
			cpuf->Flags.PowerShuttingDown = 1;
			cpuf->Flags.Restarting = 1;
		}
	}
}
void cpuf_power_handle(byte Interrupt) {
	cpuf->Flags.HasPowerInterrupt = 1;
	cpuf->PowerInterrupt = Interrupt;
}
void cpuf_power_unhandle(void) {
	cpuf->Flags.HasPowerInterrupt = 0;
}
void cpuf_power_wakeup(void) {
	if (cpuf->Flags.PowerActive) {
		cpuf->Flags.Asleep = 0;
		mmui_stackput(CPUFPWR_DATA_WAKEUP);
		cpui_fireint(cpuf->PowerInterrupt);
		return;
	}
}