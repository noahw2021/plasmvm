//
//  ops.c
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#include "cpu.h"
void(*InstructionHandlers[256])(void);

Instruction(SET) { // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction(LDWM) { // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}
Instruction (STWM) { // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16

}
Instruction (LDBM) { // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16

}
Instruction (STBM) { // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	
}
Instruction (OR) { // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction (AND) { // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16
	
}
Instruction (XOR) { // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (NOT) { // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (ADD) { // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (SUB) { // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (MUL) { // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (DIV) { // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16

}
Instruction (SETI) { // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80
	
}
Instruction (LDWMI) { // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (STWMI) { // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (LDBMI) { // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
Instruction (STBMI) { // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
}
