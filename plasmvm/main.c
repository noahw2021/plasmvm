//
//  main.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#include "ctx.h"
ictx_t* ctx;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
	ctx = malloc(sizeof(ictx_t));
	memset(ctx, 0, sizeof(ictx_t));
	
	
}
