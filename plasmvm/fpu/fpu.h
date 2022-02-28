//
//  fpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

// Implements non-trivial C floating point functions

#ifndef fpu_h
#define fpu_h
#include "../ctx.h"

#define _FPU_FACTORIALPREC 1
#define __FPU_FACTORIALB (_FPU_FACTORIALPREC * 3000)

#define __FPUENUM_SOFT	0x01
#define __FPUENUM_X86	0x02
#define __FPUENUM_X64	0x03
#define __FPUENUM_CMATH	0x04

// If you are getting compliation errors, ensure you are capable of using the desired FPU engine.
#define _FPU_TYPE __FPUENUM_X64

x32 fpus_abs(x32 Source);
x32 fpus_fact(x32 Source);
x32 fpus_sin(x32 Source);
x32 fpus_pow(x32 Power, x32 Source);
x32 fpus_rooti(int Root, x32 Source);
x32 fpus_expi(int Exponent, x32 Source);
x32 fpus_mod(x32 Divisor, x32 Source);

x64 fpud_abs(x64 Source);
x64 fpud_fact(x64 Source);
x64 fpud_sin(x64 Source);
x64 fpud_pow(x64 Power, x64 Source);
x64 fpud_rooti(int Root, x64 Source);
x64 fpud_expi(int Exponent, x64 Source);
x64 fpud_mod(x64 Divisor, x64 Source);

#endif /* fpu_h */
