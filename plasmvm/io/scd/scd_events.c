//
//  scd_events.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "scd.h"
#include "../../cpu/features/cpuf.h"

void scd_data(byte Event) {
	
}

void scdi_sendevent(byte Event) {
	switch (Event) {
		case SCD_SHUTDOWN:
			cpuf_power_shutdown();
			break;
	}
}
