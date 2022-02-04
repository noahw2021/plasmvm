//
//  io.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "io.h"
#include "kb/kb.h"
#include "term/term.h"
#include "scd/scd.h"

void io_init(void) {
	kb_init();
	term_init();
	scd_init();
}
void io_shutdown(void) {
	kb_shutdown();
	term_shutdown();
	scd_shutdown();
}

void io_clock(void) {
	term_clock();
	scd_clock();
}
