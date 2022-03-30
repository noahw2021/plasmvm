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
		}
	}
}
void cpuf_power_sleep(void) {

}
void cpuf_power_restart(void) {

}
void cpuf_power_handle(byte Interrupt) {

}
void cpuf_power_unhandle(void) {

}
void cpuf_power_wakeup(void) {

}