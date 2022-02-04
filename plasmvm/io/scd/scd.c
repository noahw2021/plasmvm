//
//  scd.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "scd.h"
scdctx_t* scdctx;

#include <stdlib.h>
#include <string.h>

// System Control Device Events

void scd_init(void) {
	scdctx = malloc(sizeof(scdctx_t));
	memset(scdctx, 0, sizeof(scdctx_t));
}

void scd_shutdown(void) {
	free(scdctx);
}

void scd_clock(void) {
	if (scdctx->Flags.CallCmd)
		ctx->ip = scdctx->CallNext;
}
