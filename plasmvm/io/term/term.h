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

#define CC_NEWLINE		0x00
#define CC_RETURN		0x01
#define CC_BEEP			0x02
#define CC_SETCOLOR		0x03
#define CC_CLRCOLOR		0x04
#define CC_SETCURX		0x05
#define CC_SETCURY		0x06

void termi_print(char Data);
void termi_sendcc(byte Code);

#endif /* term_h */
