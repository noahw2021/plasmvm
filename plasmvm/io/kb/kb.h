//
//  kb.h
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include "../../ctx.h"

typedef struct _kbctx {
	u64 Keys[4]; // bits
}kbctx_t;
extern kbctx_t* kbctx;

void kb_init(void);
void kb_shutdown(void);

void kbi_keyup(byte Scancode);
void kbi_keydown(byte Scancode);
