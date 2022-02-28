//
//  fpu_c.c
//  plasmvm
//
//  Created by Noah Wooten on 2/28/22.
//

#include <stdio.h>
#include <math.h>
#include "../fpu.h"

#if (_FPU_TYPE == __FPUENUM_CMATH)

x64 fpud_pow(x64 Power, x64 Source) {
	return pow(Power, Source);
}
x64 fpud_rooti(int Root, x64 Source) {
	return pow(1.0 / (x64)Root, Source);
}
x64 fpud_expi(int Exponent, x64 Source) {
	return pow(Exponent, Source);
}
x64 fpud_mod(x64 Divisor, x64 Source) {
	return fmod(Source, Divisor);
}
x32 fpus_pow(x32 Power, x32 Source) {
	return powf(Power, Source);
}
x32 fpus_rooti(int Root, x32 Source) {
	return powf(1.0f / (x32)Root, Source);
}
x32 fpus_expi(int Exponent, x32 Source) {
	return powf(Exponent, Source);
}
x32 fpus_mod(x32 Divisor, x32 Source) {
	return fmodf(Source, Divisor);
}

#endif
