//
//  fpu_single.c
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

#include "fpu.h"
#ifdef _APPLE
#include <math.h>
#endif

x32 fpusi_integrand(x32 x, x32 Value) {
	x32 Return;
	
	Return = pow(x, Value);
	Return *= pow(2.7182818284590452353602874, x * -1.f);
	
	return Return;
}

x32 fpus_abs(x32 Source) {
	x32 _Source = Source;
	if (Source <= 0)
		_Source *= -1.0f;
	return _Source;
}

x32 fpus_fact(x32 Source) {
	x32 Area = 0.0;
	x32 A = 0;
	x32 B = __FPU_FACTORIALB;
	x32 P = 50 * B * _FPU_FACTORIALPREC;
	x32 X = 0.0;
	
	for (u64 i = 0; i < P; i++) {
		Area += (fpusi_integrand(X, Source) * ((B - A) / P));
		X += ((B - A) / P);
	}
	
	return Area;
}
