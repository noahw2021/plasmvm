//
//  handlers.c
//  plasmvm
//
//  Created by Noah Wooten on 2/2/22.
//

#include "cpu.h"

DeclInstruction(SET);
DeclInstruction(LDWM);
DeclInstruction(STWM);
DeclInstruction(LDBM);
DeclInstruction(STBM);
DeclInstruction(OR);
DeclInstruction(AND);
DeclInstruction(XOR);
DeclInstruction(NOT);
DeclInstruction(ADD);
DeclInstruction(SUB);
DeclInstruction(MUL);
DeclInstruction(DIV);
DeclInstruction(SETI);
DeclInstruction(LDWMI);
DeclInstruction(STWMI);
DeclInstruction(LDBMI);
DeclInstruction(STBMI);
DeclInstruction(ORI);
DeclInstruction(ANDI);
DeclInstruction(XORI);
DeclInstruction(ADDI);
DeclInstruction(SUBI);
DeclInstruction(MULI);
DeclInstruction(DIVI);
DeclInstruction(SL);
DeclInstruction(SR);
DeclInstruction(SLI);
DeclInstruction(SRI);
DeclInstruction(SA);
DeclInstruction(SP);
DeclInstruction(SAI);
DeclInstruction(GO);
DeclInstruction(ENT);
DeclInstruction(RT);
DeclInstruction(RTF);
DeclInstruction(RTFI);
DeclInstruction(GOI);
DeclInstruction(ENTI);
DeclInstruction(CMP);
DeclInstruction(CMPI);
DeclInstruction(GOF);
DeclInstruction(ENTF);
DeclInstruction(ENTFI);
DeclInstruction(ENTFII);
DeclInstruction(GOFI);
DeclInstruction(GOFII);
DeclInstruction(NEG);
DeclInstruction(EIH);
DeclInstruction(DIH);
DeclInstruction(HLT);
DeclInstruction(INT);
DeclInstruction(INTI);
DeclInstruction(HND);
DeclInstruction(HNDI);
DeclInstruction(HNDII);
DeclInstruction(SPA);
DeclInstruction(SPG);
DeclInstruction(SAA);
DeclInstruction(SAG);
DeclInstruction(LDSD);
DeclInstruction(LDSDI);
DeclInstruction(STSD);
DeclInstruction(LDVM);
DeclInstruction(LDVMI);
DeclInstruction(STVM);
DeclInstruction(SPN);
DeclInstruction(MSP);
DeclInstruction(SSP);
DeclInstruction(ASP);
DeclInstruction(SPB);
DeclInstruction(SAB);
DeclInstruction(SAII);
DeclInstruction(INC);
DeclInstruction(DEC);
DeclInstruction(SBN);
DeclInstruction(SBN);
DeclInstruction(IOB);
DeclInstruction(IIB);
DeclInstruction(IOW);
DeclInstruction(IIW);
DeclInstruction(IOS);
DeclInstruction(IIS);

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
	ListInstruction(MSP),
	ListInstruction(SSP),
	ListInstruction(ASP),
	ListInstruction(SPB),
	ListInstruction(SAB),
	ListInstruction(SAII),
	ListInstruction(INC),
	ListInstruction(DEC),
	ListInstruction(SBN),
	ListInstruction(IOB),
	ListInstruction(IIB),
	ListInstruction(IOW),
	ListInstruction(IIW),
	ListInstruction(IOS),
	ListInstruction(IIS),
};
