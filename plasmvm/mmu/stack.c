//
//  stack.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "mmu.h"

word mmui_stackpull(void) {
	u64* Stack = mmu_translate(ctx->sp, _ACCESS_READ);
	u64 Return = Stack[0];
	ctx->sp += 8;
	return Return;
}
byte mmui_stackpullbyte(void) {
	byte* Stack = mmu_translate(ctx->sp, _ACCESS_READ);
	byte Return = Stack[0];
	ctx->sp += 1;
	return Return;
}

void mmui_stackput(word Value) {
	
}
void mmui_stackputbyte(byte Value) {
	
}
