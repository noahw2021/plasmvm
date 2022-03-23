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

#endif /* cpuf.h */