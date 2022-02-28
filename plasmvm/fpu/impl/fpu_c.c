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
	return 0.0;
}
x64 fpud_rooti(int Root, x64 Source) {
	return 0.0;
}
x64 fpud_expi(int Exponent, x64 Source) {
	return 0.0;
}
x64 fpud_mod(x64 Divisor, x64 Source) {
	return 0.0;
}
x32 fpus_pow(x32 Power, x32 Source) {
	return 0.0f;
}
x32 fpus_rooti(int Root, x32 Source) {
	return 0.0f;
}
x32 fpus_expi(int Exponent, x32 Source) {
	return 0.0f;
}
x32 fpus_mod(x32 Divisor, x32 Source) {
	return 0.0f;
}

#endif
