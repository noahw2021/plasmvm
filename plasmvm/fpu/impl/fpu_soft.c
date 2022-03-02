//
//  fpu_soft.c
//  plasmvm
//
//  Created by Noah Wooten on 2/28/22.
//

#include <stdio.h>
#include <math.h>
#include "../fpu.h"



x64 fpud_pow(x64 Power, x64 Source) {
	x64 Return = 1.0;
	x64 Fraction, Fraction2;
	modf(Power, &Fraction);
	if (Fraction == 0) {
		for (int i = 0; i < Power; i++) {
			Return *= Source;
		}
		return Return;
	} else {
		x64 Fraction3 = modf(Fraction, &Fraction2);
		u64 Root = (u64)(1.0 / (x64)Fraction3);
		return fpud_rooti((int)Root, fpud_pow(Fraction2, Source));
	}
}

x64 fpud_rooti(int Root, x64 Source) {
	
}

x64 fpud_expi(int Exponent, x64 Source) {

}

x64 fpud_mod(x64 Divisor, x64 Source) {

}

x32 fpus_pow(x32 Power, x32 Source) {

}

x32 fpus_rooti(int Root, x32 Source) {

}

x32 fpus_expi(int Exponent, x32 Source) {

}

x32 fpus_mod(x32 Divisor, x32 Source) {

}
