//
//  cpu_engine.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "cpu.h"
#include "features/cpuf.h"
#include "../mmu/mmu.h"

#include <stdlib.h>
#include <string.h>

void cpu_init(void) {
	ctx = malloc(sizeof(ictx_t));
	memset(ctx, 0, sizeof(ictx_t));

	cpuf_init();
	return;
}
void cpu_clock(void) {
	byte Opcode = r1();
	cpu_opcode(Opcode);
}
void cpu_opcode(byte Opcode) {
	InstructionHandlers[Opcode]();
}
void cpu_shutdown(void) {
	free(ctx);
	cpuf_shutdown();
}
