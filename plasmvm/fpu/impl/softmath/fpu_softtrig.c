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

x64 fpui_arccsc(x64 Value) {
	x64 Area = 0.0;
	if (Value >= 1.0) {
		for (x64 Pos = Value; Pos < (Value + __FPU_ARCCSCSTART); Pos += __FPU_ARCCSCINC) {
			Area += (1.0 / (Pos * fpud_rooti(2, (fpud_expi(2, Pos) - 1)))) * __FPU_ARCCSCINC;
		}
	}
	else {
		return 0.0 - fpui_arccsc(fpud_abs(Value));
	}
}

x64 fpui_arcsec(x64 Value) {
	x64 Area = 0.0;
	if (Value >= 1.0) {
		for (x64 Pos = 1.0; Pos < Value; Pos += __FPU_ARCSECINC) {
			Area += (1.0 / (Pos * fpud_rooti(2, (fpud_expi(2, Pos) - 1)))) * __FPU_ARCSECINC;
		}
	}
	else {
		return 0.0 - fpui_arcsec(fpud_abs(Value) + _FPU_PI);
	}
}

x64 fpui_arccot(x64 Value) {
	x64 Area = 0.0;
	for (x64 Pos = Value; Pos < (Value + __FPU_ARCCOTSTART); Pos += __FPU_ARCCOTADDER)
		Area += (1.0 / (fpud_expi(2, Pos) + 1)) * __FPU_ARCCOTADDER;
	return Area;
}