//
//  termdata.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "term.h"
#include <stdio.h>

void term_clock(void) {
	return; // can't think of something for this to do rn but i will keep here it in case
}
void term_data(byte Data) {
	if (InRange(Data, 0x00, 0x1F) || InRange(Data, 0x7F, 0xFF)) { // ASCII Control Codes
		switch (Data) {
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
			case 0x08:
			case 0x09:
			case 0x0A: // New Line (LF)
			case 0x0B:
			case 0x0C:
			case 0x0D: // Reset horizontal position (CR)
			case 0x0E:
			case 0x0F:
				break;
			default:
				break;
		}
	} else {
		printf("%c", Data);
	}
}
