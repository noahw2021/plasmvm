//
//  cpuf_timer.c
//  plasmvm
//
//  Created by Noah Wooten on 3/23/22.
//
#include "cpuf.h"

void cpuf_timer_set(void) {
	cpuf->Flags.Active = 1;
}
void cpuf_timer_clear(void) {
	cpuf->Flags.Active = 0;
}
void cpuf_timer_wait(u32 ms) {

}
void cpuf_timer_setint(byte Vector, u32 ms) {

}
void cpuf_timer_clrint(byte Vector) {

}