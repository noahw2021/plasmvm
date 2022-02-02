//
//  handlers.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "cpu.h"

void(*InstructionHandlers[256])(void) = {
	ListInstruction(SET),
	ListInstruction(LDWM),
	ListInstruction(STWM),
	ListInstruction(LDBM),
	ListInstruction(STBM),
	ListInstruction(OR),
	ListInstruction(AND),
	ListInstruction(XOR),
	ListInstruction(NOT),
	ListInstruction(ADD),
	ListInstruction(SUB),
	ListInstruction(MUL),
	ListInstruction(DIV),
	ListInstruction(SETI),
	ListInstruction(LDWMI),
	ListInstruction(STWMI),
	ListInstruction(LDBMI),
	ListInstruction(STBMI),
	ListInstruction(ORI),
	ListInstruction(ANDI),
	ListInstruction(XORI),
	ListInstruction(ADDI),
	ListInstruction(SUBI),
	ListInstruction(MULI),
	ListInstruction(DIVI),
	ListInstruction(SL),
	ListInstruction(SR),
	ListInstruction(SLI),
	ListInstruction(SRI),
	ListInstruction(SA),
	ListInstruction(SP),
	ListInstruction(SAI),
	ListInstruction(GO),
	ListInstruction(ENT),
	ListInstruction(RT),
	ListInstruction(RTF),
	ListInstruction(RTFI),
	ListInstruction(GOI),
	ListInstruction(ENTI),
	ListInstruction(CMP),
	ListInstruction(CMPI),
	ListInstruction(GOF),
	ListInstruction(ENTF),
	ListInstruction(ENTFI),
	ListInstruction(ENTFII),
	ListInstruction(GOFI),
	ListInstruction(GOFII),
	ListInstruction(NEG),
	ListInstruction(EIH),
	ListInstruction(DIH),
	ListInstruction(HLT),
	ListInstruction(INT),
	ListInstruction(INTI),
	ListInstruction(HND),
	ListInstruction(HNDI),
	ListInstruction(HNDII),
	ListInstruction(SPA),
	ListInstruction(SPG),
	ListInstruction(SAA),
	ListInstruction(SAG),
	ListInstruction(LDSD),
	ListInstruction(LDSDI),
	ListInstruction(STSD),
	ListInstruction(LDVM),
	ListInstruction(LDVMI),
	ListInstruction(STVM),
	ListInstruction(SPN),
};
