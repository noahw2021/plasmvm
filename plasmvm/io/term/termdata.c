//
//  termdata.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "term.h"

void term_clock(void) {
	return; // can't think of something for this to do rn but i will keep here it in case
}
void term_data(byte Data) {
	if (InRange(Data, 0x00, 0x1F) || InRange(Data, <#min#>, <#max#>)) { // ASCII Control Codes
		
	}
}
