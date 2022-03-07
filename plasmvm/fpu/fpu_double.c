//
//  fpu_double.c
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

#include "fpu.h"
#include <math.h>

x64 fpudi_integrand(x64 x, x64 Value) {
	x64 Return;
	
	Return = fpud_pow(x, Value);
	Return *= fpud_pow(2.7182818284590452353602874, x * -1.0);
	
	return Return;
}

x64 fpudi_taylorsin(int Degree, x64 Value) {
	x64 Return = 0.00;
	x64 RealValue = Value;
	if (Value > 3.1416 || Value < -3.1416) {
		RealValue = fpud_mod(3.141592653589793238462643383279, RealValue);
	}
	
	for (int i = 0; i < Degree; i++) {
		Return += (fpud_expi(i, -1.0) / fpud_fact((2 * i + 1))) * fpud_pow(Value, (2 * i + 1));
	}
	return Return;
}

x64 fpud_abs(x64 Source) {
	x64 _Source = Source;
	if (Source <= 0)
		_Source *= -1.0;
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

x64 fpud_sin(x64 Source) {
	return fpudi_taylorsin(5, Source);
}
