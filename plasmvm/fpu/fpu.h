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

x32 fpus_abs(x32 Source);
x32 fpus_fact(x32 Source);

x64 fpud_abs(x64 Source);
x64 fpud_fact(x64 Source);

#endif /* fpu_h */
