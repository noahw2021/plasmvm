//
//  translate.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "../ctx.h"
#include "mmu.h"

#define InRange(x, min, max) (x > min && x < max)

typedef union pagetableentry {
	u64 Data[3];
	struct {
		u64 Physical;
		u64 Virtual;
		u32 Size;
		union {
			byte Raw;
			struct {
				byte Execute : 1;
				byte Read : 1;
				byte Write : 1;
			};
		}Flags;
	};
}pagetableentry_t;

#ifndef NULL
#define NULL (void*)0
#endif

void* mmu_translate(word Virtual, byte Access) {
	if (VMD0_GET_ENABLED(ctx->vm0)) {
		for (int i = 0; i < VMD0_GET_PAGECNT(ctx->vm0); i++) {
			pagetableentry_t* Table = (pagetableentry_t*)((byte*)vmctx->PhysicalRam + VMD1_GET_ADDRESS(ctx->vm1));
			if (InRange(Virtual, Table->Virtual, Table->Virtual + Table->Size)) {
				if (Access & _ACCESS_READ && !Table[i].Flags.Read)
					return NULL;
				if (Access & _ACCESS_WRITE && !Table[i].Flags.Write)
					return NULL;
				if (Access & _ACCESS_EXEC && !Table[i].Flags.Execute)
					return NULL;
				return vmctx->PhysicalRam + Table[i].Physical + (Virtual - Table[i].Virtual);
			}
		}
	} else {
		return (byte*)vmctx->PhysicalRam + Virtual;
	}
	return NULL;
}
