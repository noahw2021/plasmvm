//
//  fpu_softtrig.c
//  plasmvm
//
//  Created by Noah Wooten on 3/7/22.
//

#include "../../fpu.h"
#include <math.h>

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

x64 fpui_arcsin(x64 Value) {
	x64 Return = 0.0;
	x64 RValue = fmod(Value, _FPU_PI);
	for (int i = 0; i < 12; i++) {
		Return += ((fpud_fact(2 * i)) / ((fpud_expi(i, 4)) * fpud_expi(2, fpud_fact(i)) * ((2 * i) + 1))) * (fpud_expi(((2 * i) + 1), RValue));
	}
	return Return;
}

x64 fpui_arccos(x64 Value) {
	return ((_FPU_PI / 2) - fpui_arcsin(Value));
}

x64 fpui_arctan(x64 Value) {
	x64 Area = 0.0;
	for (x64 Pos = 0.0; Pos < Value; Pos += __FPU_ARCTANINC)
		Area += (1.0 / (fpud_expi(2, Pos) + 1)) * __FPU_ARCTANINC;
	return Area;
}
