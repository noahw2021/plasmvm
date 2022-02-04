//
//  kb.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "kb.h"
#include "../../mmu/mmu.h"
#include "../../cpu/cpu.h"
kbctx_t* kbctx;

#include <stdlib.h>
#include <string.h>

void kb_init(void) {
	kbctx = malloc(sizeof(kbctx_t));
	memset(kbctx, 0, sizeof(kbctx_t));
}
void kb_shutdown(void) {
	free(kbctx);
}

void kbi_keyup(byte Scancode) {
	mmui_stackputbyte(Scancode);
	cpui_fireint(CPUINT_KEYUP);
	return;
}
void kbi_keydown(byte Scancode) {
	mmui_stackputbyte(Scancode);
	cpui_fireint(CPUINT_KEYDOWN);
	return;
}
