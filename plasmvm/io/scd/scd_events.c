//
//  scd_events.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "scd.h"

void scd_data(byte Event) {
	
}

void scdi_sendevent(byte Event) {
	switch (Event) {
		case SCD_SHUTDOWN:
			SET_HALTFLAG(ctx->sf0);
			CLR_INTFLAG(ctx->sf0);
			break;
	}
}
