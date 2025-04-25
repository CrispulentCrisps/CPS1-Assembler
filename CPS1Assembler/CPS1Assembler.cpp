//
// |----------------------------|
// |	   CPS1-Assembler		|
// |	Started in 23/04/2025	|
// |----------------------------|
// 
//	Usage
// 
//		arg1	|	Input file
//		arg2	|	Output file
//
#define _CRT_SECURE_NO_WARNINGS
#include "CPS1Assembler.h"

FILE* input;     //Input file
FILE* output;    //Output file

std::vector<VariableDef> variables;  //Variables list
std::vector<LabelDef> labels;        //Label list
std::vector<std::string> codelines;  //List of code lines
arch_type arch;

int main(int argc, char** argv)
{
	//Opening source file
	if (!OpenFile(argc, argv)) {
		std::cout << "\n\nERROR, ASSEMBLER FAILURE!";
		return 1;
	}

	//Clear out 
	variables.clear();
	labels.clear();
	codelines.clear();
	ParseLines();
	arch = DetermineArch();
	if (arch == arch_Z80)
	{
		std::cout << "\n\nZ80 arch detected";
		if (Interpret_Z80() != Z80_FINE) {
			std::cout << "\nA Z80 ASSEMBLER ERROR HAS OCCURED!";
		}
	}
	else if (arch == arch_M68K)
	{
		std::cout << "\n\nM68K arch detected";
		if (Interpret_M68K() != M68K_FINE) {
			std::cout << "\nA M68K ASSEMBLER ERROR HAS OCCURED!";
		}
	}
	else
	{
		std::cout << "\nERROR, NO ARCH FOUND\nMISSING arch_Z80 OR arch_M68K";
	}

	std::cout << "\nVariables\n";
	for (int x = 0; x < variables.size(); x++)
	{
		std::cout << "\nVar name: " << variables[x].Name << "\nVar location: " << std::hex << variables[x].memloc;
	}

	std::cout << "\nLabels\n";
	for (int x = 0; x < labels.size(); x++)
	{
		std::cout << "\nLabel name: " << labels[x].Name << "\nLabel Start: " << std::hex << labels[x].startloc << "\nLabel End: " << std::hex << labels[x].endloc;
	}

	return 0;
}

void ParseLines()
{
	int panic = 0;
	char line[4096];
	while (fgets(line, sizeof(line), input))
	{
		codelines.push_back(line);
		std::cout << line;
		panic++;
		if (panic > 9999999) return;
		ParseLines();
	}
}

//Read through file to identify Z80 commands
int Interpret_Z80()
{
	for (int x = 0; x < codelines.size(); x++)
	{
		std::string curline = codelines[x];		//Current line instruction
		std::string linebuf = "";				//Buffer for reading correct instruction
		for (int y = 0; y < codelines[x].size(); y++)
		{
			linebuf += codelines[x][y];
			//Check for label names, make sure labels have at least 1 character more than just :
			if (y < codelines[x].size())
			{
				if (linebuf[y] == LABEL_END && linebuf.size() > 1)
				{
					labels.push_back(AddLabel(linebuf));
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

	for (int x = 0; x < Z80_len; x++)
	{
		if (comcheck == Z80_opcode_ident[x]) return x;
	}
	return COM_NULL;
}
//Call appropriate function based off of command type
void HandleComType_Z80(int comind, int lineind)
{
	switch (comind)
	{
	case LD:
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
		break;
	case HALT:
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

//Generate bytecode based on Z80 instruction set
int Generate_Z80()
{
	return Z80_FINE;
}

int Interpret_M68K()
{
	return M68K_FINE;
}

int Generate_M68K()
{
	return M68K_FINE;
}

//Determine which architecture the file is
arch_type DetermineArch()
{
	for (int x = 0; x < codelines.size(); x++)
	{
		if (codelines[x] == ex_keyword_ident[arch_Z80]) { return Z80; }
		else if (codelines[x] == ex_keyword_ident[arch_M68K]) { return M68K; }
	}
	return NOARCH;
}

LabelDef AddLabel(std::string name)
{
	LabelDef label;
	label.Name = name;
	label.startloc = 0x0000;
	label.endloc = 0xFFFF;
	return label;
}

//Determine if a current command is an assembler specific command
int DetermineAssemblerCommand(std::string com)
{
	for (int x = 0; x < ex_len; x++)
	{
		if (com == ex_keyword_ident[x]) return x;
	}
	return COM_NULL;
}

bool OpenFile(int argc, char** argv)
{
	//Check arguments
	for (int i = 0; i < argc; ++i) { std::cout << argv[i] << "\n"; }

	//Check if file is empty
	if (argv[1] == NULL) {
		std::cout << "NO FILENAME GIVEN";
		return false;
	}

	//Open input file
	input = fopen(argv[1], "rb");
	if (input == NULL)
	{
		char buf[256];
		memcpy(buf, argv[1], strlen(argv[1]));
		std::cout << "ERROR, NO FILE FOUND AT: " << buf;
		return 1;
	}

	//Output file for the target architecture
	output = fopen(argv[2], "wb");

	////Find file size
	//fseek(input, 0, SEEK_END);
	//int size = ftell(input);
	//rewind(input);

	return true;
}