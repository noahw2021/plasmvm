//
//  kb.h
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "../../ctx.h"

void kb_init(void);
void kb_shutdown(void);

void kbi_keyup(byte Scancode);
void kbi_keydown(byte Scancode);
