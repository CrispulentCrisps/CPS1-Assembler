//Storing data types, enums and constants

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//Asm functions
#define ASM_MAXCHARS	0x0FFF	//Max characters in the linebuffer for parsing

//Assembler conditions
#define Z80_FINE 		0
#define M68K_FINE 		0

//Label identifiers
#define LABEL_END		':'		//Character to check for end of label
#define SUBLABEL_START	'.'		//Character to check for the start of a sublabel

//Token identifiers
#define TOKEN_IMM		'#'
#define TOKEN_HEX		'$'
#define TOKEN_BIN		'%'
#define TOKEN_BOPEN		'('
#define TOKEN_BCLOSE	')'
#define TOKEN_SEPERATOR ','
#define TOKEN_ADD		'+'
#define TOKEN_SUB		'-'
#define TOKEN_MUL		'*'
#define TOKEN_DIV		'/'
#define TOKEN_AND		'&'
#define TOKEN_OR		'|'
#define TOKEN_XOR		'^'
#define TOKEN_NOT		'~'

//List of exclusive characters
#define TAB				"\t"	//Tab character
#define RETURN			"\n"	//Newline character
#define SPACE			" "		//Space character
#define COMMENT			";"		//Comment identifier

#define VAR_SET			"="		//Assigner for variable data

//Command identifiers
#define COM_NULL		0xFFFF

typedef unsigned char	u8;
typedef signed char		s8;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned long	u32;
typedef signed long		s32;

//Architecture for current file
enum arch_type {
	ARCT_NoArch,		//Used for checking if the file has an architecture
	ARCT_Z80,			//Z80 architecture
	ARCT_M68K,			//M68K architecture
};

enum com_type {
	BAD,				//Bad command type, something has went wrong
	ASM,				//Assembler command
	Z80,				//Z80 command
	M68K,				//M68K command
};

//List of keywords for Z80 opcodes, sourced here:https://www.zilog.com/docs/z80/um0080.pdf and https://clrhome.org/table/
enum Z80_keywords {
	//Instructions
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
	RLC,
	RLCA,
	RLA,
	RRC,
	RRCA,
	RRA,
	RL,
	RR,
	SLA,
	SRA,
	SRL,
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
	z80_opcode_len,
};

enum Z80_registers {
	A,
	B,
	C,
	D,
	E,
	F,
	H,
	L,
	R,
	AF,
	AFp,			//Equal to AF'
	BC,
	DE,
	HL,
	IX,
	IXpD,		//Equal to IX+D
	IXH,
	IXL,
	IY,
	IYpD,		//Equal to IY+D
	IYH,
	IYL,
	I,
	SP,
	z80_reg_len,
};

//Extra commands specific to the assembler and not of any chips
enum ex_keyword {
	arch_Z80,		//Set architecutre to Z80
	arch_M68K,		//Set architecutre to M68K
	incsrc,			//Include source file
	incbin,			//Include binary file
	org,			//Set code destination
	db,				//Data byte	[u8
	dw,				//Data word [u16]
	dl,				//Data long [u32]

	ex_len,			//Length of extra keywords enum
};

enum num_type {
	n_dec,			//Decimal			|	Raw decimal value					|	4
	n_hex,			//Hexadecimal		|	Denoted with $ before the value		|	$04
	n_bin,			//Binary			|	Denoted with 0b before the value	|	0b00000100
};

enum addr_type {
	imm,			//Immediate			|	Denoted with a # before the value	|	ld A, #$09
	ptr,			//Pointer			|	Denoted as a pair of parenthises	|	ld A, (BC)
	loc,			//Memory location	|	Deonted as the raw value			|	ld A, $02
};

enum token_type {
	//universal
	t_number,			//Handles all numbers regardless of type
	t_ident,			//Identifiers for variables, constants
	t_bropen,			//Opening bracket,			(
	t_brclose,			//Closing bracket,			)
	t_seperator,		//Seperator character		,
	t_imm,				//Immediate character		#

	//Arch specific
	t_Z80_reg,			//Z80 register
	t_M68K_reg,			//M68K register

	//Mathematics
	t_add,				//Addition character,		+
	t_sub,				//Subtraction character,	-
	t_mul,				//Multiplication character, *
	t_div,				//Division character,		/
	t_and,				//Bitwise AND,				&
	t_or,				//Bitwise OR,				|
	t_xor,				//Bitwise XOR,				^
	t_not,				//Bitwise NOT,				~

	token_len,
};

//List of identifiable command types in the Z80 architecture
extern std::string Z80_opcode_ident[z80_opcode_len];

extern std::string Z80_register_ident[z80_reg_len];

extern std::string Z80_args_ident[ex_len];

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

typedef struct {
	u32 bytecode;		//Bytecode of command
	u32 value;			//Value of command
	com_type type;		//Type of command
	u8 id;				//Current ID of command
} ComLine;

typedef struct {
	token_type type;	//
	u32 value;			//
} Token;

extern std::vector<VariableDef> Variables;				//Variables list
extern std::vector<LabelDef> Labels;					//Label list
extern std::vector<std::string> CodeLines;				//List of code lines
extern std::vector<ComLine> ComList;					//List of parsed commands
extern arch_type arch;									//Current architecture type