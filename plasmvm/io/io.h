//
//  io.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef io_h
#define io_h
#include "../ctx.h"

void io_init(void);
void io_shutdown(void);

void io_clock(void);

void io_data(byte Port, byte Data);
byte io_get(byte Port);

#endif /* io_h */
