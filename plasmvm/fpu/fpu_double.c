//
//  fpu_double.c
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

#include "fpu.h"
#ifdef __APPLE__
#include <math.h>
#endif

x64 fpudi_integrand(x64 x, x64 Value) {
	x64 Return;
	
	Return = pow(x, Value);
	Return *= pow(2.7182818284590452353602874, x * -1.f);
	
	return Return;
}

x64 fpud_abs(x64 Source) {
	x64 _Source = Source;
	if (Source <= 0)
		_Source *= -1.0f;
	return _Source;
}

x64 fpud_fact(x64 Source) {
	x64 Area = 0.0;
	x64 A = 0;
	x64 B = __FPU_FACTORIALB;
	x64 P = 50 * B * _FPU_FACTORIALPREC;
	x64 X = 0.0;
	
	for (u64 i = 0; i < P; i++) {
		Area += (fpudi_integrand(X, Source) * ((B - A) / P));
		X += ((B - A) / P);
	}
	
	return Area;
}
