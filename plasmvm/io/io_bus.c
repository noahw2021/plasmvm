//
//  io_bus.c
//  plasmvm
//
//  Created by Noah Wooten on 2/8/22.
//

#include "io.h"
#include "scd/scd.h"
#include "kb/kb.h"
#include "term/term.h"

void io_data(byte Port, byte Data) {
	switch (Port) {
		case 0: // SCD
			scd_data(Data);
			break;
		case 1: // Keyboard
			kbi_keydown(Data);
			break;
		case 2: // Terminal
			term_data(Data);
			break;
	}
}
byte io_get(byte Port) {
	switch (Port) {
		case 0:
			return 0;
		case 1:
			return 0;
		case 2:
			return 0;
	}
	return 0;
}
