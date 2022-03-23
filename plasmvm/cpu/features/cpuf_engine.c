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


}

void cpuf_shutdown(void) {

}