//Storing data types, enums and constants

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char	u8;
typedef signed char		s8;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned long	u32;
typedef signed long		s32;

//Architecture for current file
enum arch_type {
	Z80,
	M68K,
};

//List of keywords for Z80 opcodes, sourced here: https://www.zilog.com/docs/z80/um0080.pdf and https://clrhome.org/table/
enum Z80_keywords {
	//Opcodes
	LD,
	PUSH,
	POP,
	EX,
	EXX,
	LDI,
	LDIR,
	LDD,
	LDDR,
	CPI,
	CPIR,
	CPD,
	CPDR,
	ADD,
	ADC,
	SUB,
	SBC,
	AND,
	OR,
	XOR,
	CP,
	INC,
	DEC,
	DAA,
	CPL,
	NEG,
	CCF,
	SCF,
	NOP,
	HALT,
	DI,
	EI,
	IM0,
	IM1,
	IM2,
	RLCA,
	RLA,
	RRCA,
	RRA,
	RL,
	RR,
	SLA,
	SRA,
	RLD,
	RRD,
	BIT,
	SET,
	RES,
	JP,
	JR,
	DJNZ,
	CALL,
	RET,
	RETI,
	RETN,
	RST,
	IN,
	INI,
	IND,
	INDR,
	OUT,
	OUTI,
	OTIR,
	OUTD,
	OTDR,
	opcode_len,

	//Main registers
	A,
	B,
	C,
	D,
	E,
	F,
	H,
	L,
	AF,
	BC,
	DE,
	HL,
	IX,
	IXH,
	IXL,
	IY,
	IYH,
	IYL,
	SP,
	PC,

	//Length
	Z80_len,
};

//Extra commands specific to the assembler and not of any chips
enum ex_keyword {
	incsrc,			//Include source file
	incbin,			//Include binary file
	org,			//Set code destination
	db,				//Data byte	[u8
	dw,				//Data word [u16]

	ex_len,			//Length of extra keywords enum
};

enum num_type {
	dec,			//Decimal			|	Raw decimal value					|	4
	hex,			//Hexadecimal		|	Denoted with $ before the value		|	$04
	bin,			//Binary			|	Denoted with 0b before the value	|	$0b00000100
};

enum addr_type {
	imm,			//Immediate			|	Denoted with a # before the value	|	ld A, #$09
	ptr,			//Pointer			|	Denoted as a pair of parenthises	|	ld A, (BC)
	loc,			//Memory location	|	Deonted as the raw value			|	ld A, $02
};

std::string Z80_opcode_ident[opcode_len] = {
	"LD ",
	"PUSH ",
	"POP ",
	"EX ",
	"EXX ",
	"LDI ",
	"LDIR ",
	"LDD ",
	"LDDR ",
	"CPI ",
	"CPIR ",
	"CPD ",
	"CPDR ",
	"ADD ",
	"ADC ",
	"SUB ",
	"SBC ",
	"AND ",
	"OR ",
	"XOR ",
	"CP ",
	"INC ",
	"DEC ",
	"DAA ",
	"CPL ",
	"NEG ",
	"CCF ",
	"SCF ",
	"NOP ",
	"HALT ",
	"DI ",
	"EI ",
	"IM0 ",
	"IM1 ",
	"IM2 ",
	"RLCA ",
	"RLA ",
	"RRCA ",
	"RRA ",
	"RL ",
	"RR ",
	"SLA ",
	"SRA ",
	"RLD ",
	"RRD ",
	"BIT ",
	"SET ",
	"RES ",
	"JP ",
	"JR ",
	"DJNZ ",
	"CALL ",
	"RET ",
	"RETI ",
	"RETN ",
	"RST ",
	"IN ",
	"INI ",
	"IND ",
	"INDR ",
	"OUT ",
	"OUTI ",
	"OTIR ",
	"OUTD ",
	"OTDR ",
};

//Variables, defined as
//
//	VarName1 = $20
//	VarName2 = $0210
//	VarName3 = $100210
//
typedef struct {
	std::string Name;	//Name of variable
	u32 memloc;			//Memory location of variable
} VariableDef;

//Definition of labels in code, defined as
//
//	MainLabel:
//		.SubLabel:
//
//Every label must end with a : except as arguments for a conditional branch
//
typedef struct {
	std::string Name;	//Name of variable
	u32 startloc;		//Starting memory location of variable
	u32 endloc;			//Ending memory location of variable
} LabelDef;