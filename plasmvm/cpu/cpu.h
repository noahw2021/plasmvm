//
//  cpu.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef cpu_h
#define cpu_h
#include "../ctx.h"

/*
 Instructions in enum follow the below format
 NAME[tab]= 0xNN, // DESCRIPTION (NAME [(R|I,D):(PSZ,USZ)]):TISZ
 
 Where NAME is the Instruction's name
 Where DESCRIPTION is the Instruction's functional description
 Where (R|I) represents R, I, or F depending on if the value is a Register, Immediate or Floating (Special)
	Register.
 Where D is the Operand's name.
 Where PSZ is the allocated size of the operand in bits.
 Where USZ is the usable size of the operand in bits.
 Where TISZ is the total size of the instruction in bits.
 Where NN is the total size of the opcode. See example below.
 
 Differences between PSZ and USZ occur when needed to be used as padding when an instruction's argument size in bits not divisible by 8 (or byte size on architecture).
 
 Example:
 
 MOV[tab]= 0x00, // Moves an operand into a register (MOV [R:(4,8),DEST] [I:(64,64),SRC]):80
 
 Where "MOV" is the Instruction's name
 Where "Moves an operand into a register" is the Instruction's description
 Where "[R:(4,8),DEST]" signifies that the operand "DEST" is a register physically stored in 8 bits but only 4 should be used by the instruction.
 Where "I:(64,64),SRC]" signifies that the operand "SRC" is an immediate value physically stored in 64 bits and that all 64 bits are available to be used by the compiler.
 Where ":80" signifies that the instruction is in total 80 bits long. This is determined by (8 + 8 + 64), with 8 being the size of the opcode, 8 being the size of the 1st operand and 64 being the size of the 2nd operand.
 Where "00" signifies the opcode's value. May be larger or smaller than 8 bits. Zeros should be used to prefix the size if it cannot be represented (Each instruction must have the same opcode length).
 */

enum {
	__SET = 0x00, // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	__LDWM = 0x01, // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STWM = 0x02, // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__LDBM = 0x03, // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STBM = 0x04, // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__OR = 0x05, // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16
	__AND = 0x06, // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16
	__XOR = 0x07, // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16
	__NOT = 0x08, // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16
	__ADD = 0x09, // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16
	__SUB = 0x0A, // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16
	__MUL = 0x0B, // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16
	__DIV = 0x0C, // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16
	__SETI = 0x0D, // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__LDWMI = 0x0E, // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__STWMI = 0x0F, // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__LDBMI = 0x10, // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__STBMI = 0x11, // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80
	__ORI = 0x12, // Logical OR Immediate (ORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__ANDI = 0x13, // Logical AND Immediate (ANDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__XORI = 0x14, // Logical XOR Immediate (XORI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__ADDI = 0x15, // Sum Register and Immediate (ADDI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__SUBI = 0x16, // Subtract Immediate from Register (SUBI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__MULI = 0x17, // Multiply Register by Immediate (MULI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__DIVI = 0x18, // Divide Register By Immediate (DIVI [R:(4,8),DEST] [I:(64,64),SRC]):80
	__SL = 0x19, // Shift Left (SL [R:(4,4),DEST] [R:(4,4),AMT]):16
	__SR = 0x1A, // Shift Right (SR [R:(4,4),DEST] [R:(4,4),AMT]):16
	__SLI = 0x1B, // Shift Left Immediate (SLI [R:(4,8),SRC] [I:(6,8),AMT]):24
	__SRI = 0x1C, // Shift Right Immediate (SRI [R:(4,8),SRC] [I:(6,8,AMT]):24
	__SA = 0x1D, // Stack Add (Push) (SA [R:(4,8),SRC]):16
	__SP = 0x1E, // Stack Pull (SP [R:(4,8),DEST]):16
	__SAI = 0x1F, // Stack Add (Push) Immediate (SAI [I:(64, 64)]):72
	__GO = 0x20, // Go (Jump) (GO [R:(4,8),LOCATION]):16
	__ENT = 0x21, // Enter (Call) (GO [R:(4,8),LOCATION]):16
	__RT = 0x22, // Return (RT):8
	__RTF = 0x23, // Return if Flag (RTF [R:(4,8),FLAG]):16
	__RTFI = 0x24, // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72
	__GOI = 0x25, // Go (Jump) Immediate (GOI [I:(64,64),LOCATION]):72
	__ENTI = 0x26, // Enter (Call) Immediate (ENTI [I:(64,64),LOCATION]):72
	__CMP = 0x27, // Compare Registers (CMP [R:(4,4),COMPARE0] [R:(4,4),COMPARE1]):16
	__CMPI = 0x28, // Compare Register with Immediate (CMPI [R:(4,8),COMPARE0] [I:(64,64),COMPARE1]):80
	__GOF = 0x29, // Go if Flag (GOF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	__ENTF = 0x2A, // Enter if Flag (ENTF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16
	__GOFI = 0x2B, // Go if Flag Immediate (GOFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	__ENTFI = 0x2C, // Enter if Flag Immediate (ENTFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80
	__GOFII = 0x2D, // Go if Flag Immediate Immediate  (GOFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	__ENTFII = 0x2E, // Enter if Flag Immediate Immediate (ENTFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136
	__NEG = 0x2F, // Signed Negate Register (NEG [R:(4,8)]):16
	__NOP = 0x30, // No Operation (NOP):8
	__EIH = 0x31, // Enable Interrupt Handling (EIH):8
	__DIH = 0x32, // Disable Interrupt Handling (DIH):8
	__HLT = 0x33, // Enter Halt State (HLT):8
	__INT = 0x34, // Call Interrupt (INT [R:(4,8),INTERRUPT]):8
	__INTI = 0x35, // Call Interrupt Immediate (INTI [I:(8,8),INTERRUPT]):16
	__HND = 0x36, // Handle Interrupt (HND [R:(4,4),INTERRUPT] [R:(4,4),LOCATION]):16
	__HNDI = 0x37, // Handle Interrupt Immediate (HNDI [I:(8,8),INTERRUPT] [R:(4,8),LOCATION]):24
	__HNDII = 0x38, // Handle Interrupt Immediate Immediate (HNDII [I:(8,8),INTERRUPT] [I:(64,64),LOCATION]):80
	__SPA = 0x39, // Stack Pull All (SPA):8
	__SPG = 0x3A, // Stack Pull General (SPG):8
	__SAA = 0x3B, // Stack Add (Push) All (SAA):8
	__SAG = 0x3C, // Stack Add (Push) General (SAG):8
	__LDSD = 0x3D, // Load System Descriptor (LDSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDSDI = 0x3E, // Load System Descriptor Immediate (LDSDI [I:(64,64),PART0] [I:(64,64),PART1]):136
	__STSD = 0x3F, // Store System Descriptor to Registers (STSD [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDVM = 0x40, // Load Virtual Descriptor from Registers (LDVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	__LDVMI = 0x41, // Load Virtual Descriptor from Immediates (LDVMI [I:(64,64),PART0] [I:(64,64),PART1]):136
	__STVM = 0x42, // Store Virtual Descriptor to Registers (STVM [R:(4,4),PART0] [R:(4,4),PART1]):16
	__SPN = 0x43, // Stack Pull No Operand (SPN):8
	__MSP = 0x44, // Multiply Stack Pointer (DATA is multiplied by IMM) (MSP [R:(4,4),DATA] [I:(20,20),IMM]):32
	__SSP = 0x45, // Subtract Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA] [I:(20,20),IMM]):32
	__ASP = 0x47, // Add Stack Pointer (DATA is multiplied by IMM) (ASP [R:(4,4),DATA] [I:(20,20),IMM]):32
	__SPB = 0x48, // Stack Pull Byte (SPB [R:(4,8),DEST]):16
	__SAB = 0x49, // Stack Add Byte (SAB [R:(4,8),SRC]):16
	__SAII = 0x4A, // Stack Add Byte Immediate (SAII [I:(8,8),SRC]):16
	__INC = 0x4B, // Increment (INC [R:(4,8),SRC]):16
	__DEC = 0x4C, // Decrement (DEC [R:(4,8),SRC]):16
	__SBN = 0x4D, // Stack Pull Byte No Operand (SBN):8
	__IOB = 0x4E, // I/O Output Byte (IOB [R:(4,4),PORT] [R:(4,4),DATA]):16
	__IIB = 0x4F, // I/O Input Byte (IIB [R:(4,4),PORT] [R:(4,4),DATA]):16
	__IOW = 0x50, // I/O Output Word (IOW [R:(4,4),PORT] [R:(4,4),DATA]):16
	__IIW = 0x51, // I/O Input Word (IIW [R:(4,4),PORT] [R:(4,4),DATA]):16
	__IOS = 0x52, // I/O Output String (IOB [R:(4,4),PORT] [R:(4,4),DATA] [R:(4,8),LEN]):24
	__IIS = 0x53, // I/O Input String (IOB [R:(4,4),PORT] [R:(4,4),STR] [R:(4,8),LEN]):24
	__LDHM = 0x54, // Load Register Half-Word from Memory (LDHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STHM = 0x55, // Store Register Half-Word in Memory (STHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__LDHMI = 0x56, // Load Immediate Half-Word from Memory (LDHM [R:(4,8),DEST] [I:(32,32),SRC]):48
	__STHMI = 0x57, // Store Immediate Half-Word in Memory (STHM [R:(4,8),DEST] [I:(32,32),SRC):48
	__LDQM = 0x58, // Load Register Quarter-Word from Memory (LDQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__STQM = 0x59, // Store Register Quarter-Word from Memory (STQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16
	__LDQMI = 0x5A, // Load Immediate Quarter-Word from Memory (LDQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	__STQMI = 0x5B, // Store Immediate Quarter-Word from Memory (STQM [R:(4,8),DEST] [I:(16,16),SRC]):32
	__STWMII = 0x5C, // Store Immediate Immediate Word in Memory (STWMII [I:(64,64),DEST] [I:(64,64),SRC]):136
	__STHMII = 0x5D, // Store Immediate Immediate Half Word in Memory (STHMII [I:(64,64),DEST] [I:(32,32),SRC]):104
	__STQMII = 0x5E, // Store Immediate Immediate Quarter Word in Memory (STQMII [I:(64,64),DEST] [I:(16,16),SRC]):88
	__STBMII = 0x5F, // Store Immediate Immediate Byte in Memory (STBMII [I:(64,64),DEST] [I:(8,8),SRC]):80
	__GFCPS = 0x60, // Get Floating CoProcessor Status (GFCPS [R:(4,8),DEST]):16
	__SFDP = 0x61, // Set Floating Double Precision (SFDP):8
	__CFDP = 0x62, // Clear Floating Double Precision (CFDP):8
	__TFRX = 0x63, // Exchange Floating with Regular Register (TFRX [F:(4,4),FP_REG] [R:(4,4),INT_REG]):16
	__CFRI = 0x64, // Convert Floating to Regular Integer (CFRI [F:(4,4),FP_REG] [R:(4,4),INT_REG]):16
	__CFFI = 0x65, // Convert Floating to Floating Integer (CFFI [F:(4,4),FP_REG0] [F:(4,4),FP_REG1]):16
	__LSFR = 0x66, // Load Single Precision Float from Register (LSFR [F:(4,4),FP_DEST] [R:(4,4),INT_SRC]):16
	__LDFR = 0x67, // Load Double Precision Float from Register (LSFR [F:(4,4),FP_DEST] [R:(4,4),INT_SRC]):16
	__FABS = 0x68, // Floating Absolute Value (FABS [F:(4,8),SRC]):16
	__FADD = 0x69, // Floating Addition (FADD [F:(4,4),SRC] [F:(4,4),ADDER]):16
	__FADDT = 0x6A, // Floating Addition To (FADDT [F:(4,4),SRC] [F:(4,4),ADDER] [F:(4,8),DST]):24
	__FSUB = 0x6B, // Floating Subtraction (FSUB [F:(4,4),SRC] [F:(4,4),SUBBER]):16
	__FSUBT = 0x6C, // Floating Subtraction To (FSUBT [F:(4,4),SRC] [F:(4,4),SUBBER], [F:(4,8),DEST]):24
	__FMUL = 0x6D, // Floating Multiply (FMUL [F:(4,4),SRC] [F:(4,4),FACTOR]):16
	__FMULT = 0x6E, // Floating Multiply To (FMULT [F:(4,4),SRC] [F:(4,4),FACTOR] [F:(4,8),DEST]):24
	__FDIV = 0x6F, // Floating Divide (FDIV [F:(4,4),SRC] [F:(4,4),DIVISOR]):16
	__FDIVT = 0x70, // Floating Divide To (FDIVT [F:(4,4),SRC] [F:(4,4),DIVISOR] [F:(4,8),DEST]):24
	__FMOD = 0x71, // Floating Modulo (FMOD [F:(4,4),SRC] [F:(4,4),DIVISOR]):16
	__FMODT = 0x72, // Floating Modulo To (FMODT [F:(4,4),SRC] [F:(4,4),DIVISOR] [F:(4,8),DEST]):24
	__FSIN = 0x73, // Floating Sine{x} (FSIN [F:(4,8),SRC]):16
	__FSINT = 0x74, // Floating Sine{x} To (FSINT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FCOS = 0x75, // Floating CoSine{x} (FCOS [F:(4,8),SRC]):16
	__FCOST = 0x76, // Floating CoSine{x} To (FCOST [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FTAN = 0x77, // Floating Tangent{x} (FTAN [F:(4,8),SRC]):16
	__FTANT = 0x78, // Floating Tangnet{x} To (FTANT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FSEC = 0x79, // Floating Secant{x} (FSEC [F:(4,8),SRC]):16
	__FSECT = 0x7A, // Floating Secant{x} To (FSECT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FCSC = 0x7B, // Floating CoSecant{x} (FCSC [F:(4,8),SRC]):16
	__FCSCT = 0x7C, // Floating CoSecant{x} To (FCSCT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FEXP = 0x7D, // Floating Exponent (FEXP [F:(4,4),BASE] [F:(4,4),EXPONENT]):16
	__FEXPI = 0x7E, // Floating Exponent Integer (FEXPI [F:(4,4),BASE] [R:(4,4),EXPONENT]):16
	__FEXPII = 0x7F, // Floating Exponent Immediate Integer (FEXPII [F:(4,8),BASE] [I:(16,16),EXPONENT]):32
	__FEXPT = 0x80, // Floating Exponent To (FEXPT [F:(4,4),BASE] [F:(4,4),EXPONENT] [F:(4,8),DEST]):24
	__FEXPIT = 0x81, // Floating Exponent Integer To (FEXPIT [F:(4,4),BASE] [R:(4,4),EXPONENT] [F:(4,8),DEST]):24
	__FEXPIIT = 0x82, // Floating Exponent Immediate To Integer (FEXPIIT [F:(4,8),BASE] [I:(16,16),EXPONENT] [F:(4,8),DEST]):40
	__FNSIN = 0x83, // Floating Inverse Sine{x} (FNSIN [F:(4,8),SRC]):16
	__FNSINT = 0x84, // Floating Inverse Sine{x} To (FNSINT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FNCOS = 0x85, // Floating Inverse CoSine{x} (FNCOS [F:(4,8),SRC]):16
	__FNCOST = 0x86, // Floating Inverse CoSine{x} To (FNCOST [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FNTAN = 0x87, // Floating Inverse Tangent{x} (FNTAN [F:(4,8),SRC]):16
	__FNTANT = 0x88, // Floating Inverse Tangent{x} To (FNTANT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FNSEC = 0x89, // Floating Inverse Secant{x} (FNSEC [F:(4,8),SRC]):16
	__FNCSC = 0x8A, // Floating Inverse CoSecant{x} (FNCSC [F:(4,8),SRC]):16
	__FNCOT = 0x8B, // Floating Inverse CoTangent{x} (FNCOT [F:(4,8),SRC]):16
	__FNSECT = 0x8C, // Floating Inverse Secant{x} To (FNSECT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FNCSCT = 0x8D, // Floating Inverse CoSecant{x} To (FNCSCT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FNCOTT = 0x8E, // Floating Inverse CoTangent{x} To (FNCOTT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FINC = 0x8F, // Floating Increment (FINC [F:(4,8),REG]):16
	__FDEC = 0x90, // Floating Decrement (FDEC [F:(4,8),REG]):16
	__FNEG = 0x91, // Floating Negate (FNEG [F:(4,8),REG]):16
	__F1OX = 0x92, // Floating 1/x (F1OX [F:(4,8),REG]):16
	__FFCT = 0x93, // Floating Factorial (FFCT [F:(4,8),REG]):16
	__FFSF = 0x94, // Floating Flip Sign (FFSF [F:(4,8),REG]):16
	__FAIF = 0x95, // Floating Add Floating With Regular (FAIF [F:(4,4),SRC] [R:(4,4),REG]):16
	__FSIF = 0x96, // Floating Sub Floating With Regular (FSIF [F:(4,4),SRC] [R:(4,4),REG]):16
	__FMIF = 0x97, // Floating Multiply Floating With Regular (FMIF [F:(4,4),SRC] [R:(4,4),REG]):16
	__FDIF = 0x98, // Floating Divison Floating With Regular (FDIF [F:(4,4),SRC] [R:(4,4),REG]):16
	__FMODIF = 0x99, // Floating Modulo Floating With Regular (FMODIF [F:(4,4),SRC] [R:(4,4),REG]):16
	__FAIFI = 0x9A, // Floating Add Floating with Regular (FAIFI [F:(4,8), SRC] [I:(64,64),IMMT]):80
	__FSIFI = 0x9B, // Floating Subtract Floating with Regular (FSIFI [F:(4,8),SRC] [I:(64,64),IMMT]):80
	__FMIFI = 0x9C, // Floating Multiply Floating with Regular (FMIFI [F:(4,8),SRC] [I:(64,64),IMMT]):80
	__FDIFI = 0x9D, // Floating Division Floating with Regular (FDIFI [F:(4,8),SRC] [I:(64,64),IMMT]):80
	__FMODIFI = 0x9E, // Floating Modulo Floating with Regular (FMODIFI [F:(4,8),SRC] [I:(64,64),IMMT]):80
	__FLOG2 = 0x9F, // Floating Log2{x} (FLOG2 [F:(4,4),SRC] [F:(4,4),VAL]):16
	__FLOG10 = 0xA0, // Floating Log10{x} (FLOG10 [F:(4,4),SRC] [F:(4,4),VAL]):16
	__FLOGE = 0xA1, // Floating Ln{x} (FLOGE [F:(4,4),SRC] [F:(4,4),VAL]):16
	__FE10X = 0xA2, // Floating 10^x (FE10X [F:(4,4),SRC] [F:(4,4),VAL]):16
	__FNOP = 0xA3, // Floating No Operation (FNOP):8
	__F2XM1 = 0xA4, // Flating {2^x}-1 (F2XM1 [F:(4,4),SRC] [F:(4,4),VAL]):16
	__FCMPFR = 0xA5, // Floating Compare Float Regular (FCMPFR [F:(4,4),VAL0] [R:(4,4),VAL1]):16
	__FCMPFF = 0xA6, // Floating Compare Float Float (FCMPFF [F:(4,4),VAL0] [F:(4,4),VAL1]):16
	__FCMPFRI = 0xA7, // Floating Compare Float Regular{Imm} (FCMPFRI [F:(4,8),VAL0] [I:(64,64),VAL1]):80
	__FCMPFFI = 0xA8, // Floating Compare Float Float{Imm} (FCMPFFI [F:(4,8),VAL0] [I:(64,64),VAL1]):80
	__FEEX = 0xA9, // Floating e^x (FEEX [F:(4,8),SRC]):16
	__CFFT = 0xAA, // Copy Floating Flags to System Flags (CFFT):8
	__FSQRT = 0xAB, // Floating square root (FSQRT [F:(4,8),SRC]):16
	__FCBRT = 0xAC, // Floating cubic root (FCBRT [F:(4,8),SRC]):16
	__FNRTI = 0xAD, // Floating nth-root (FNRT [I:(4,4),ROOT] [F:(4,4),SRC]):16
	__FLOG2I = 0xAE, // Floating Log2{x}{Imm} (FLOG2I [F:(4,8),DEST] [I:(64,64),VALUE]):80
	__FLOG10I = 0xAF, // Floating Log10{x}{Imm} (FLOG10I [F:(4,8),DEST] [I:(64,64),VALUE]):80
	__FLOGEI = 0xB0, // Floating Ln{x}{Imm} (FLOGEI [F:(4,8),DEST] [I:(64,64),VALUE]):80
	__FLOG2R = 0xB1, // Floating Log2{x} with Regular (FLOG2R [F:(4,4),DEST] [R:(4,4),VALUE]):16
	__FLOG10R = 0xB2, // Floating Log10{x} with Regular (FLOG10R [F:(4,4),DEST] [R:(4,4),VALUE]):16
	__FLOGER = 0xB3, // Floating Ln{x} with Regular (FLOGER [F:(4,4),DEST] [R:(4,4),VALUE]):16
	__FNRTX = 0xB4, // Floating nth-root with large root (FNRTX [I:(32,32),ROOT] [F:(4,8),SRC]):48
	__FCOT = 0xB5, // Floating CoTangent{x} (FCOT [F:(4,8),SRC]):16
	__FCOTT = 0xB6, // Floating CoTangent{x} To (FCOTT [F:(4,4),SRC] [F:(4,4),DEST]):16
	__FABST = 0xB7, // Floating Absolute Value To (FABS [F:(4,4),SRC] [F:(4,4),DEST]):16
	__CPUFQ = 0xB8, // CPU Feature Query (CPUFQ [R:(4,4),FEATURE] [R:(4,4),DEST]):16
	__CPUFS = 0xB9, // CPU Feature Set {Enabled} (CPUFQ [R:(4,8),FEATURE]):16
	__CPUFC = 0xBA, // CPU Feature Clear {Disabled} (CPUFQ [R:(4,8),FEATURE]):16
	__CPUFDB = 0xBB, // CPU Feature SendData Byte (CPUFDB [R:(4,4),FEATURE] [R:(4,4),DATA]):16
	__CPUFDQ = 0xBC, // CPU Feature SendData QuarterWord (CPUFDQ [R:(4,4),FEATURE] [R:(4,4),DATA]):16
	__CPUFDH = 0xBD, // CPU Feature SendData HalfWord (CPUFDH [R:(4,4),FEATURE] [R:(4,4),DATA]):16
	__CPUFDW = 0xBE, // CPU Feature SendData Word (CPUFDW [R:(4,4),FEATURE] [R:(4,4),DATA]):16
	__CPUFRB = 0xBF, // CPU Feature RecvData Byte (CPUFRB [R:(4,4),FEATURE] [R:(4,4),DEST]):16
	__CPUFRQ = 0xC0, // CPU Feature RecvData QuarterWord (CPUFRQ [R:(4,4),FEATURE] [R:(4,4),DEST]):16
	__CPUFRH = 0xC1, // CPU Feature RecvData HalfWord (CPUFRH [R:(4,4),FEATURE] [R:(4,4),DEST]):16
	__CPUFRW = 0xC2, // CPU Feature RecvData Word (CPUFRW [R:(4,4),FEATURE] [R:(4,4),DEST]):16
};

extern void(*InstructionHandlers[256])(void);

#define Instruction(Name) void Name(void)
#define ListInstruction(Name) [__##Name] = Name
#define DeclInstruction(Name) void Name(void);

void cpu_init(void);
void cpu_clock(void);
void cpu_opcode(byte Opcode);
void cpu_shutdown(void);

#define CPUINT_KEYDOWN	0x00
#define CPUINT_KEYUP	0x01
#define CPUINT_SCDREQ	0x02

void cpui_fireint(byte Interrupt);

void cpui_go(word Address);
void cpui_enter(word Address);
void cpui_return(void);
void cpui_pushall(void);
void cpui_pushgen(void);
void cpui_pullall(void);
void cpui_pullgen(void);

void cpuf_init(void);
void cpuf_shutdown(void);

void cpuf_timer_set(void);
void cpuf_timer_clear(void);
void cpuf_timer_wait(u32 ms);
void cpuf_timer_setint(byte Vector, u32 ms);
void cpuf_timer_clrint(byte Vector);

void cpuf_power_set(void);
void cpuf_power_clear(void);
void cpuf_power_shutdown(void);
void cpuf_power_sleep(void);
void cpuf_power_restart(void);

#endif /* cpu_h */
