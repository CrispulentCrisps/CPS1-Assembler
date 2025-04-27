#include "CPS1Assembler.h"
#include "Z80.h"
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
	com.type = Z80;

	std::vector<Token> tlist;
	tlist.clear();	
	//Find arguments, if they exist then tokenise
	std::string args = GetInstructionArgs_Z80(comind, CodeLines[lineind]);
	if (args != "") { TokeniseArguments(&tlist, args); }

	switch (comind)
	{
	case LD:
		Determine_LD(&tlist);
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
		break;
	case LDIR:
		break;
	case LDD:
		break;
	case LDDR:
		break;
	case CPI:
		break;
	case CPIR:
		break;
	case CPD:
		break;
	case CPDR:
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
		break;
	case CPL:
		break;
	case NEG:
		break;
	case CCF:
		break;
	case SCF:
		break;
	case NOP:
		com.bytecode = 0x00;
		break;
	case HALT:
		com.bytecode = 0x76;
		break;
	case DI:
		break;
	case EI:
		break;
	case IM0:
		break;
	case IM1:
		break;
	case IM2:
		break;
	case RLCA:
		break;
	case RLA:
		break;
	case RRCA:
		break;
	case RRA:
		break;
	case RL:
		break;
	case RR:
		break;
	case SLA:
		break;
	case SRA:
		break;
	case RLD:
		break;
	case RRD:
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
		break;
	case RST:
		break;
	case IN:
		break;
	case INI:
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
		break;
	case OTDR:
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

void Determine_LD(std::vector<Token>* tokens)
{
	for (int x = 0; x < tokens->size(); x++)
	{
		//If register
		if (tokens->at(x).type == t_Z80_reg)
		{
			Token arg0 = tokens->at(x);
			Token arg1 = tokens->at(fmin(x + 1, tokens->size()));
			Token arg2 = tokens->at(fmin(x + 2, tokens->size()));
			Token arg3 = tokens->at(fmin(x + 3, tokens->size()));
			//Reg arg 0
			if (arg0.value >= A && arg0.value <= L)
			{
				if (arg0.value == A)
				{

				}
			}

		}
	}
}