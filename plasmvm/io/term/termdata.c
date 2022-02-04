//
//  termdata.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "term.h"
#include <stdio.h>

void term_data(byte Data) {
	if (termctx->Flags.PendingData) {
		if (termctx->Flags.DataIterator == 3)
			termctx->Flags.PendingData = 0;
		union {
			u32 Big;
			byte Small[4];
		}MedInt;
		MedInt.Big = termctx->PendingData;
		MedInt.Small[++termctx->Flags.DataIterator] = Data;
		termctx->PendingData = MedInt.Big;
	}
	if (InRange(Data, 0x00, 0x1F) || InRange(Data, 0x7F, 0xFF)) { // ASCII Control Codes
		switch (Data) {
			case 0x00: // Clear Screen
				termi_sendcc(CC_CLEAR);
				break;
			case 0x01: // Set Color
				termi_sendcc(CC_SETCOLOR);
				break;
			case 0x02: // Clear Color
				termi_sendcc(CC_CLRCOLOR);
				break;
			case 0x03: // Begin Recieve Data 4
				termctx->Flags.PendingData = 1;
				break;
			case 0x04: // Send Data
				termi_bigdata(termctx->PendingData);
				break;
			case 0x05: // Set Cursor X
				termi_sendcc(CC_SETCURX);
				break;
			case 0x06: // Set Cursor Y
				termi_sendcc(CC_SETCURY);
				break;
			case 0x07: // Bell (BEL)
				termi_sendcc(CC_BEEP);
				break;
			case 0x08:
				break;
			case 0x09:
				break;
			case 0x0A: // New Line (LF)
				termi_sendcc(CC_NEWLINE);
				break;
			case 0x0B:
				break;
			case 0x0C:
				break;
			case 0x0D: // Reset horizontal position (CR)
				termi_sendcc(CC_RETURN);
				break;
			case 0x0E:
				break;
			case 0x0F:
				break;
			default:
				break;
		}
	} else {
		printf("%c", Data);
	}
}
