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
#define CC_CLEAR		0x07

void termi_print(char Data);
void termi_bigdata(u32 Data);
void termi_sendcc(byte Code);

typedef struct _termctx {
	u32 Color;
	u32 CursorX;
	u32 CursorY;
	u32 BigData;
	union {
		u16 Raw;
		struct {
			byte PendingData : 1;
			byte DataIterator : 2;
		};
	}Flags;
	u32 PendingData;
}termctx_t;
extern termctx_t* termctx;

#endif /* term_h */
