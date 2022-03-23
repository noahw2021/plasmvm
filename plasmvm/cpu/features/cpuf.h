//
//  cpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef cpuf_h
#define cpuf_h
#include "../../ctx.h"

typedef struct _cpufctx {
	u32 TimerMs;
	byte Interrupt;
	union {
		byte Flags;
		struct {
			byte Active : 1;
		};
	}Flags;
}cpufctx_t;
extern cpufctx_t* cpuf;

void cpuf_init(void);
void cpuf_shutdown(void);

void cpuf_timer_set(void);
void cpuf_timer_clear(void);
void cpuf_timer_wait(u32 ms);
void cpuf_timer_setint(byte Vector, u32 ms);
void cpuf_timer_clrint(byte Vector);

void cpuf_power_set(void);
void cpuf_power_clear(void);
void cpuf_power_shutdown(void);
void cpuf_power_sleep(void);
void cpuf_power_restart(void);

#endif /* cpuf.h */