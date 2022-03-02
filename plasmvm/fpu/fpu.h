//
//  fpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

#ifndef fpu_h
#define fpu_h
#include "../ctx.h"

#define _FPU_FACTORIALPREC  1
#define _FPU_SINEPREC	    1

#define __FPUENUM_SOFT	0x01
#define __FPUENUM_CMATH	0x02

// If you are getting compliation errors, ensure you are capable of using the desired FPU engine.
#define _FPU_TYPE __FPUENUM_SOFT

// Abstracted higher level functions
x32 fpus_abs(x32 Source);
x32 fpus_fact(x32 Source);
x32 fpus_sin(x32 Source);

x64 fpud_abs(x64 Source);
x64 fpud_fact(x64 Source);
x64 fpud_sin(x64 Source);

// Lower component functions, should be optimized
x64 fpud_pow(x64 Power, x64 Source);
x64 fpud_rooti(int Root, x64 Source);
x64 fpud_expi(int Exponent, x64 Source);
x64 fpud_mod(x64 Divisor, x64 Source);
x32 fpus_pow(x32 Power, x32 Source);
x32 fpus_rooti(int Root, x32 Source);
x32 fpus_expi(int Exponent, x32 Source);
x32 fpus_mod(x32 Divisor, x32 Source);

x32 fpuf32_getsignificand(x32 Source);
x64 fpuf64_getsignificand(x64 Source);

// Declarations for helper functions
#define __FPU_FACTORIALB (_FPU_FACTORIALPREC * 3000)
#define __FPU_TAYLORPREC (5 * _FPU_SINEPREC)
#endif /* fpu_h */
