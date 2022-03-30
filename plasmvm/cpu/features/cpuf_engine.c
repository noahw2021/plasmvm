//
//  cpuf_engine.c
//  plasmvm
//
//  Created by Noah Wooten on 3/23/22.
//
#include "cpuf.h"
cpufctx_t* cpuf;

#include <stdlib.h>
#include <string.h>

void cpuf_init(void) {
	cpuf = malloc(sizeof(cpufctx_t));
	memset(cpuf, 0, sizeof(cpufctx_t));
	cpuf->Flags.TimerAvailable = 1;
	cpuf->Flags.PowerAvailable = 1;

}

void cpuf_shutdown(void) {
	free(cpuf);
}


byte cpuf_query(byte Device) {
	switch (Device) {
	case CPUFENUM_TIMER:
		if (cpuf->Flags.TimerAvailable)
			return 1;
		else
			return 0;
		break;
	case CPUFENUM_POWER:
		if (cpuf->Flags.PowerAvailable)
			return 1;
		else 
			return 0;
		break;
	default:
		return 0;
		break;
	}
}
void cpuf_send(byte Device, int Count, u64 Data) {
	switch (Device) {
	case CPUFENUM_TIMER:
		if ((Data & 0xFF) == CPUFTMR_CMD_SET)
			cpuf_timer_set();
		if ((Data & 0xFF) == CPUFTMR_CMD_CLEAR)
			cpuf_timer_clear();
		if ((Data & 0xFF) == CPUFTMR_CMD_CLRMODE)
			cpuf->Waiting.Mode = 255;
		if ((Data & 0xFF) == CPUFTMR_CMD_GO) {
			if (cpuf->Waiting.Mode == 1) { // wait
				cpuf->Interrupt = cpuf->Waiting.Interrupt;
				cpuf_timer_wait(cpuf->Waiting.Ms);
			}
			if (cpuf->Waiting.Mode == 2) { // repeat
				cpuf_timer_setint(cpuf->Waiting.Interrupt, cpuf->Waiting.Ms);
			}
		}
		if ((Data & 0xFF) == CPUFTMR_CMD_SETINT) {
			cpuf->Waiting.Interrupt = (Data & 0xFF00) >> 8;
		}
		if ((Data & 0xFF) == CPUFTMR_CMD_SETMODE) {
			cpuf->Waiting.Mode = (Data & 0xFF00) >> 8;
		}
		if ((Data & 0xFF) == CPUFTMR_CMD_SETMS) {
			cpuf->Waiting.Ms = (Data & 0xFFFFFFFF00) >> 8;
		}
		break;
	case CPUFENUM_POWER:
		if ((Data & 0xFF) == CPUFPWR_CMD_CLR) {
			cpuf_power_clear();
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_HANDLE) {
			cpuf_power_handle((Data & 0xFF00) >> 8);
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_RESTART) {
			cpuf_power_restart();
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_SET) {
			cpuf_power_set();
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_SHUTDOWN) {
			cpuf_power_shutdown();
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_SLEEP) {
			cpuf_power_sleep();
		}
		if ((Data & 0xFF) == CPUFPWR_CMD_UNHANDLE) {
			cpuf_power_unhandle();
		}
		break;
	}
}
u64 cpuf_get(byte Device, int Count) {
	return 0; // no commands recieve data as of yet
}

void cpuf_genset(byte Device) {
	switch (Device) {
	case CPUFENUM_POWER:
		cpuf_power_set();
		break;
	case CPUFENUM_TIMER:
		cpuf_timer_set();
		break;
	}
}
void cpuf_genclr(byte Device) {
	switch (Device) {
	case CPUFENUM_POWER:
		cpuf_power_clear();
		break;
	case CPUFENUM_TIMER:
		cpuf_timer_clear();
		break;
	}
}