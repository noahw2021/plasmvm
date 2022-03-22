//
//  fpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/24/22.
//

#ifndef fpu_h
#define fpu_h
#include "../ctx.h"

// Fixed Constants
#define _FPU_PI 3.141592653589693

// Precision Controls
#define _FPU_FACTORIALPREC  10
#define _FPU_SINEPREC	    10
#define _FPU_ARCTANPREC     10
#define _FPU_ARCSINPREC     10
#define _FPU_ARCCOTPREC     10
#define _FPU_ARCSECPREC     10
#define _FPU_ARCCSCPREC     10

// Enumerations
#define __FPUENUM_SOFT	0x01
#define __FPUENUM_CMATH	0x02

// If you are getting compliation errors, ensure you are capable of using the desired FPU engine.
#define _FPU_TYPE __FPUENUM_SOFT

// Abstracted higher level functions
x32 fpus_abs(x32 Source);
x32 fpus_fact(x32 Source);
x32 fpus_sin(x32 Source);
x32 fpus_cos(x32 Source);
x32 fpus_tan(x32 Source);
x32 fpus_round(x32 Source);

x64 fpud_abs(x64 Source);
x64 fpud_fact(x64 Source);
x64 fpud_sin(x64 Source);
x64 fpud_cos(x64 Source);
x64 fpud_tan(x64 Source);
x64 fpud_round(x64 Source);

// Lower component functions, should be optimized
x64 fpud_pow(x64 Power, x64 Source);
x64 fpud_rooti(int Root, x64 Source);
x64 fpud_expi(int Exponent, x64 Source);
x64 fpud_mod(x64 Divisor, x64 Source);
x64 fpud_log2(x64 Source);
x64 fpud_logx(int Base, x64 Source);
x64 fpud_ln(x64 Source);
x64 fpud_sin(x64 Source);
x64 fpud_cos(x64 Source);
x64 fpud_tan(x64 Source);
x64 fpud_csc(x64 Source);
x64 fpud_sec(x64 Source);
x64 fpud_cot(x64 Source);
x64 fpud_arcsin(x64 Source);
x64 fpud_arccos(x64 Source);
x64 fpud_arctan(x64 Source);
x64 fpud_arccsc(x64 Source);
x64 fpud_arcsec(x64 Source);
x64 fpud_arccot(x64 Source);

x32 fpus_pow(x32 Power, x32 Source);
x32 fpus_rooti(int Root, x32 Source);
x32 fpus_expi(int Exponent, x32 Source);
x32 fpus_mod(x32 Divisor, x32 Source);
x32 fpus_log2(x32 Source);
x32 fpus_logx(int Base, x32 Source);
x32 fpus_ln(x32 Source);
x32 fpus_round(x32 Source);
x32 fpus_sin(x32 Source);
x32 fpus_cos(x32 Source);
x32 fpus_tan(x32 Source);
x32 fpus_csc(x32 Source);
x32 fpus_sec(x32 Source);
x32 fpus_cot(x32 Source);
x32 fpus_arcsin(x32 Source);
x32 fpus_arccos(x32 Source);
x32 fpus_arctan(x32 Source);
x32 fpus_arccsc(x32 Source);
x32 fpus_arcsec(x32 Source);
x32 fpus_arccot(x32 Source);

x64 fpui_rooti(x64 Number, int Root);
x64 fpui_log(int Base, x64 Value);
x64 fpui_ln(x64 Value);
x64 fpui_round(x64 Value);
x64 fpui_sin(x64 Value);
x64 fpui_cos(x64 Value);
x64 fpui_tan(x64 Value);
x64 fpui_arcsin(x64 Value);
x64 fpui_arccos(x64 Value);
x64 fpui_arctan(x64 Value);
x64 fpui_arccsc(x64 Value);
x64 fpui_arcsec(x64 Value);
x64 fpui_arccot(x64 Value);

// Declarations for helper functions
#define __FPU_FACTORIALB (_FPU_FACTORIALPREC * 300)
#define __FPU_TAYLORPREC (5 * _FPU_SINEPREC)
#define __FPU_ARCTANINC  (0.05 / _FPU_ARCTANPREC)
#define __FPU_ARCSINDEG  (1 * _FPU_ARCSINPREC)
#define __FPU_ARCCOTSTART (300 * _FPU_ARCCOTPREC)
#define __FPU_ARCCOTADDER (0.05 / _FPU_ARCCOTPREC)
#define __FPU_ARCSECINC (0.05 / _FPU_ARCSECPREC)
#define __FPU_ARCCSCINC (0.05 / _FPU_ARCCSCPREC)
#define __FPU_ARCCSCSTART (300 * _FPU_ARCCSCPREC)
#endif /* fpu_h */
