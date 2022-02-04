//
//  scd.h
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#ifndef scd_h
#define scd_h
#include "../../ctx.h"

#define SCD_SHUTDOWN	0x00
#define SCD_REBOOT		0x01
#define SCD_LOCK		0x02

void scd_init(void);
void scd_shutdown(void);

void scd_clock(void);
void scd_data(byte Event);

void scdi_sendevent(byte Event);
void scdi_sethandler(byte Event, u64 Handler);

typedef struct _scdctx {
	byte PendingCommand;
	u64 CallNext;
	union {
		u16 Raw;
		struct {
			byte CallCmd;
		};
	}Flags;
}scdctx_t;
extern scdctx_t* scdctx;

#endif /* scd_h */
