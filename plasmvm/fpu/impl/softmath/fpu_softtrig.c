//
//  fpu_softtrig.c
//  plasmvm
//
//  Created by Noah Wooten on 3/7/22.
//

#include "../../fpu.h"

x64 fpui_sin(x64 Value) {
	x64 Sum = 0.0;
	x64 RValue = fpud_mod(_FPU_PI, Value);
	for (int i = 0; i < 11; i++) {
		Sum += (fpud_expi(i, -1.0) / (fpud_fact((2 * i) + 1))) * fpud_expi((2 * i) + 1, RValue);
	}
	return Sum;
}

x64 fpui_cos(x64 Value) {
	x64 Sum = 0.0;
	x64 RValue = fpud_mod(_FPU_PI, Value);
	for (int i = 0; i < 11; i++) {
		Sum += (fpud_expi(i, -1.0) / (fpud_fact((2 * i)))) * fpud_expi((2 * i), RValue);
	}
	return Sum;
}

x64 fpui_tan(x64 Value) {
	return fpui_sin(Value) / fpui_cos(Value);
}
