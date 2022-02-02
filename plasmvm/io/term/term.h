//
//  term.h
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#ifndef term_h
#define term_h
#include "../../ctx.h"

void term_init(void);
void term_shutdown(void);

void term_clock(void);
void term_data(byte Data);

#endif /* term_h */
