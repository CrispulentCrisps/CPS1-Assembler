#include "CPS1Assembler.h"
#include "Z80.h"
TokenTableEntry LDList[LDA_INST_LEN] = {
	LD_LOAD_IMM(BC,				0x01),
	LD_LOAD_IMM(B,				0x06),
	LD_LOAD_IMM(C,				0x0E),
	LD_LOAD_IMM(DE,				0x11),
	LD_LOAD_IMM(D,				0x16),
	LD_LOAD_IMM(E,				0x1E),
	LD_LOAD_IMM(HL,				0x21),
	LD_LOAD_IMM(H,				0x26),
	LD_LOAD_IMM(L,				0x2E),
	LD_LOAD_IMM(SP,				0x31),
	LD_LOAD_IMM(A,				0x3E),
	LD_LOAD_REG(B,	B,			0x40),
	LD_LOAD_REG(B,	C,			0x41),
	LD_LOAD_REG(B,	D,			0x42),
	LD_LOAD_REG(B,	E,			0x43),
	LD_LOAD_REG(B,	H,			0x44),
	LD_LOAD_REG(B,	L,			0x45),
	LD_LOAD_REG(B,	A,			0x47),
	LD_LOAD_REG(C,	B,			0x48),
	LD_LOAD_REG(C,	C,			0x49),
	LD_LOAD_REG(C,	D,			0x4A),
	LD_LOAD_REG(C,	E,			0x4B),
	LD_LOAD_REG(C,	H,			0x4C),
	LD_LOAD_REG(C,	L,			0x4D),
	LD_LOAD_REG(C,	A,			0x4F),
	LD_LOAD_REG(D,	B,			0x50),
	LD_LOAD_REG(D,	C,			0x51),
	LD_LOAD_REG(D,	D,			0x52),
	LD_LOAD_REG(D,	E,			0x53),
	LD_LOAD_REG(D,	H,			0x54),
	LD_LOAD_REG(D,	L,			0x55),
	LD_LOAD_REG(D,	A,			0x57),
	LD_LOAD_REG(E,	B,			0x58),
	LD_LOAD_REG(E,	C,			0x59),
	LD_LOAD_REG(E,	D,			0x5A),
	LD_LOAD_REG(E,	E,			0x5B),
	LD_LOAD_REG(E,	H,			0x5C),
	LD_LOAD_REG(E,	L,			0x5D),
	LD_LOAD_REG(E,	A,			0x5F),
	LD_LOAD_REG(H,	B,			0x60),
	LD_LOAD_REG(H,	C,			0x61),
	LD_LOAD_REG(H,	D,			0x62),
	LD_LOAD_REG(H,	E,			0x63),
	LD_LOAD_REG(H,	H,			0x64),
	LD_LOAD_REG(H,	L,			0x65),
	LD_LOAD_REG(H,	A,			0x67),
	LD_LOAD_REG(L,	B,			0x68),
	LD_LOAD_REG(L,	C,			0x69),
	LD_LOAD_REG(L,	D,			0x6A),
	LD_LOAD_REG(L,	E,			0x6B),
	LD_LOAD_REG(L,	H,			0x6C),
	LD_LOAD_REG(L,	L,			0x6D),
	LD_LOAD_REG(L,	A,			0x6F),
	LD_LOAD_REG(A,	B,			0x78),
	LD_LOAD_REG(A,	C,			0x79),
	LD_LOAD_REG(A,	D,			0x7A),
	LD_LOAD_REG(A,	E,			0x7B),
	LD_LOAD_REG(A,	H,			0x7C),
	LD_LOAD_REG(A,	L,			0x7D),
	LD_LOAD_REG(A,	A,			0x7F),
	LD_LOAD_REG(SP,	HL,			0xF9),
	LD_LOAD_REG(I,	A,			0xED47),
	LD_LOAD_REG(R,	A,			0xED4F),
	LD_LOAD_REG(A,	I,			0xED57),
	LD_LOAD_REG(A,	R,			0xED5F),
	LD_LOAD_REG_LOC(HL,	B,		0x70),
	LD_LOAD_REG_LOC(HL,	C,		0x71),
	LD_LOAD_REG_LOC(HL,	D,		0x72),
	LD_LOAD_REG_LOC(HL,	E,		0x73),
	LD_LOAD_REG_LOC(HL,	H,		0x74),
	LD_LOAD_REG_LOC(HL,	L,		0x75),
	LD_LOAD_REG_LOC(HL,	A,		0x77),
	LD_LOAD_REG_PTR(B,	HL,		0x46),
	LD_LOAD_REG_PTR(C,	HL,		0x4E),
	LD_LOAD_REG_PTR(D,	HL,		0x56),
	LD_LOAD_REG_PTR(E,	HL,		0x5E),
	LD_LOAD_REG_PTR(H,	HL,		0x66),
	LD_LOAD_REG_PTR(L,	HL,		0x6E),
	LD_LOAD_REG_PTR(A,	HL,		0x7E),
	LD_LOAD_WLOC_REG(BC,		0xED43),
	LD_LOAD_WLOC_REG(DE,		0xED53),
	LD_LOAD_WLOC_REG(SP,		0xED63),
	LD_LOAD_REG_WLOC(BC,		0xED4B),
	LD_LOAD_REG_WLOC(DE,		0xED5B),
	LD_LOAD_REG_WLOC(SP,		0xED6B),
	LD_LOAD_IMM(IX,				0xDD21),
	LD_LOAD_WLOC_REG(IX,		0xDD22),
	LD_LOAD_REG_WLOC(IX,		0xDD2A),
	LD_LOAD_INDpD_IMM(IX,		0xDD36),
	LD_LOAD_INDpD_REG(IX, B,	0xDD70),
	LD_LOAD_INDpD_REG(IX, C,	0xDD71),
	LD_LOAD_INDpD_REG(IX, D,	0xDD72),
	LD_LOAD_INDpD_REG(IX, E,	0xDD73),
	LD_LOAD_INDpD_REG(IX, H,	0xDD74),
	LD_LOAD_INDpD_REG(IX, L,	0xDD75),
	LD_LOAD_INDpD_REG(IX, A,	0xDD77),
	LD_LOAD_REG_INDpD(IX, B,	0xDD46),
	LD_LOAD_REG_INDpD(IX, C,	0xDD4E),
	LD_LOAD_REG_INDpD(IX, D,	0xDD56),
	LD_LOAD_REG_INDpD(IX, E,	0xDD5E),
	LD_LOAD_REG_INDpD(IX, H,	0xDD66),
	LD_LOAD_REG_INDpD(IX, L,	0xDD6E),
	LD_LOAD_REG_INDpD(IX, A,	0xDD7E),
	LD_LOAD_REG(SP,		  IX,	0xDD7E),
	LD_LOAD_INDpD_IMM(IY,		0xDD36),
	LD_LOAD_INDpD_REG(IY, B,	0xDD70),
	LD_LOAD_INDpD_REG(IY, C,	0xDD71),
	LD_LOAD_INDpD_REG(IY, D,	0xDD72),
	LD_LOAD_INDpD_REG(IY, E,	0xDD73),
	LD_LOAD_INDpD_REG(IY, H,	0xDD74),
	LD_LOAD_INDpD_REG(IY, L,	0xDD75),
	LD_LOAD_INDpD_REG(IY, A,	0xDD77),
	LD_LOAD_REG_INDpD(IY, B,	0xFD46),
	LD_LOAD_REG_INDpD(IY, C,	0xFD4E),
	LD_LOAD_REG_INDpD(IY, D,	0xFD56),
	LD_LOAD_REG_INDpD(IY, E,	0xFD5E),
	LD_LOAD_REG_INDpD(IY, H,	0xFD66),
	LD_LOAD_REG_INDpD(IY, L,	0xFD6E),
	LD_LOAD_REG_INDpD(IY, A,	0xFD7E),
	LD_LOAD_REG(SP,		  IY,	0xFD7E),
};
std::string Z80_opcode_ident[z80_opcode_len] = {
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
	"RLC ",
	"RLCA ",
	"RLA ",
	"RRC ",
	"RRCA ",
	"RRA ",
	"RL ",
	"RR ",
	"SLA ",
	"SRA ",
	"SRL ",
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
	"INIR ",
	"IND ",
	"INDR ",
	"OUT ",
	"OUTI ",
	"OTIR ",
	"OUTD ",
	"OTDR ",
};

std::string Z80_register_ident[z80_reg_len] = {
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"H",
	"L",
	"R",
	"AF",
	"BC",
	"DE",
	"HL",
	"IX",
	"IX+D",
	"IXH",
	"IXL",
	"IY",
	"IY+D",
	"IYH",
	"IYL",
	"I",
	"SP",
};

//Read through file to identify Z80 commands
int Interpret_Z80()
{
	for (int x = 0; x < CodeLines.size(); x++)
	{
		std::string curline = CodeLines[x];		//Current line instruction
		std::string linebuf = "";				//Buffer for reading correct instruction
		for (int y = 0; y < CodeLines[x].size(); y++)
		{
			linebuf += CodeLines[x][y];
			//Check for label names, make sure labels have at least 1 character more than just :
			if (y < CodeLines[x].size())
			{
				if (linebuf[y] == LABEL_END && linebuf.size() > 1)
				{
					Labels.push_back(AddLabel(linebuf));
					break;
				}
			}
			//Clear linebuf if these characters found
			if (linebuf == TAB || linebuf == RETURN || linebuf == SPACE) { linebuf = ""; }
			//Skip line read if current line is a comment
			else if (linebuf == COMMENT) { break; }

			//If a usable command has been found
			int command = DetermineCommand_Z80(linebuf);
			if (command != COM_NULL)
			{
				HandleComType_Z80(command, x);
				break;
			}

			//Check if the command is an assembler specific command
			command = DetermineAssemblerCommand(linebuf);
			if (command != COM_NULL)
			{

				break;
			}

			//Otherwise continue reading
		}
	}
	return Z80_FINE;
}

//Determine if current command is a Z80 command
int DetermineCommand_Z80(std::string com)
{
	std::string comcheck = com;
	//Set string to be uppercase for matching command list
	for (int x = 0; x < com.size(); x++)
	{
		comcheck[x] = toupper(com[x]);
	}

	for (int x = 0; x < z80_opcode_len; x++)
	{
		if (comcheck == Z80_opcode_ident[x]) return x;
	}
	return COM_NULL;
}
//Call appropriate function based off of command type
void HandleComType_Z80(int comind, int lineind)
{
	ComLine com = ComLine();

	std::vector<Token> tlist;
	tlist.clear();	
	//Find arguments, if they exist then tokenise
	std::string args = GetInstructionArgs_Z80(comind, CodeLines[lineind]);
	if (args != "") { TokeniseArguments(&tlist, args); }

	switch (comind)
	{
	case LD:
		com = Determine_LD(&tlist);
		break;
	case PUSH:
		break;
	case POP:
		break;
	case EX:
		break;
	case EXX:
		break;
	case LDI:
		com.bytecode = 0xEDA0;
		break;
	case LDIR:
		com.bytecode = 0xEDB0;
		break;
	case LDD:
		com.bytecode = 0xEDA8;
		break;
	case LDDR:
		com.bytecode = 0xEDA8;
		break;
	case CPI:
		com.bytecode = 0xEDA1;
		break;
	case CPIR:
		com.bytecode = 0xEDB1;
		break;
	case CPD:
		com.bytecode = 0xEDA9;
		break;
	case CPDR:
		com.bytecode = 0xEDB9;
		break;
	case ADD:
		break;
	case ADC:
		break;
	case SUB:
		break;
	case SBC:
		break;
	case AND:
		break;
	case OR:
		break;
	case XOR:
		break;
	case CP:
		break;
	case INC:
		break;
	case DEC:
		break;
	case DAA:
		com.bytecode = 0x27;
		break;
	case CPL:
		break;
	case NEG:
		com.bytecode = 0xED44;
		break;
	case CCF:
		com.bytecode = 0x3F;
		break;
	case SCF:
		com.bytecode = 0x37;
		break;
	case NOP:
		com.bytecode = 0x00;
		break;
	case HALT:
		com.bytecode = 0x76;
		break;
	case DI:
		com.bytecode = 0xF3;
		break;
	case EI:
		com.bytecode = 0xFB;
		break;
	case IM0:
		com.bytecode = 0xED46;
		break;
	case IM1:
		com.bytecode = 0xED56;
		break;
	case IM2:
		com.bytecode = 0xED5E;
		break;
	case RLCA:
		com.bytecode = 0x07;
		break;
	case RLA:
		com.bytecode = 0x17;
		break;
	case RRCA:
		com.bytecode = 0x0F;
		break;
	case RRA:
		com.bytecode = 0x1F;
		break;
	case RL:
		com.bytecode = 0x1F;
		break;
	case RR:
		break;
	case SLA:
		break;
	case SRA:
		break;
	case RLD:
		com.bytecode = 0xED6F;
		break;
	case RRD:
		com.bytecode = 0xED67;
		break;
	case BIT:
		break;
	case SET:
		break;
	case RES:
		break;
	case JP:
		break;
	case JR:
		break;
	case DJNZ:
		break;
	case CALL:
		break;
	case RET:
		break;
	case RETI:
		break;
	case RETN:
		com.bytecode = 0xED45;
		break;
	case RST:
		break;
	case IN:
		break;
	case INI:
		break;
	case INIR:
		break;
	case IND:
		break;
	case INDR:
		break;
	case OUT:
		break;
	case OUTI:
		break;
	case OTIR:
		break;
	case OUTD:
		com.bytecode = 0xEDAB;
		break;
	case OTDR:
		com.bytecode = 0xEDBB;
		break;
	}
}

std::string GetInstructionArgs_Z80(int comind, std::string line)
{
	std::string buf;
	for (int x = Z80_opcode_ident[comind].size(); x < line.size(); x++)
	{
		//Load up current line
		buf += line[x];
		//Remove all spaces, tabs and returns
		if (buf == TAB || buf == SPACE || buf == RETURN) { buf = ""; }
	}
	return buf;
}

ComLine Determine_LD(std::vector<Token>* tokens)
{
	ComLine output = ComLine();
	output.type = Z80;
	int tind = 0; //Token index
	int opval = 0;

	for (int x = 0; x < LDA_INST_LEN; x++)
	{

	}

	//Load could not be determined
	return output;
}