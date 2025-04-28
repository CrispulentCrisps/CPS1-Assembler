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

std::vector<LabelDef> Labels;			//Label list
std::vector<std::string> CodeLines;		//List of code lines
std::vector<ComLine> ComList;			//List of parsed commands
arch_type arch;

std::string ex_keyword_ident[ex_len] = {
	"arch_Z80",
	"arch_M68K",
	"incsrc ",
	"incbin ",
	"org ",
	"db ",
	"dw ",
	"dl ",
};

int main(int argc, char** argv)
{
	//Opening source file
	if (!OpenFile(argc, argv)) {
		std::cout << "\n\nERROR, ASSEMBLER FAILURE!";
		return 1;
	}

	//Clear out lists
	Labels.clear();
	CodeLines.clear();
	//Read through file and store to array
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
	}
	else
	{
		std::cout << "\nERROR, NO ARCH FOUND\nMISSING arch_Z80 OR arch_M68K";
	}

	std::cout << "\nLabels\n";
	for (int x = 0; x < Labels.size(); x++)
	{
		std::cout << "\nLabel name: " << Labels[x].Name << "\nLabel Start: " << std::hex << Labels[x].startloc << "\nLabel End: " << std::hex << Labels[x].endloc;
	}

	return 0;
}

int Interpret_M68K()
{
	return M68K_FINE;
}

int Generate_M68K()
{
	return M68K_FINE;
}

//Read file and split into lines
void ParseLines()
{
	char line[ASM_MAXCHARS];
	while (fgets(line, sizeof(line), input))
	{
		CodeLines.push_back(line);
		std::cout << line;
	}
}

//Determine which architecture the file is
arch_type DetermineArch()
{
	for (int x = 0; x < CodeLines.size(); x++)
	{
		if (CodeLines[x] == ex_keyword_ident[arch_Z80]) { return ARCT_Z80; }
		else if (CodeLines[x] == ex_keyword_ident[arch_M68K]) { return ARCT_M68K; }
	}
	return ARCT_NoArch;
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

int ReadNumber(std::string line, int& index, num_type type)
{
	std::string buf = "";
	for (int x = index; x < line.size(); x++)
	{
		//Decimal check
		if (type == n_dec)
		{
			if (line[x] >= '0' && line[x] <= '9')
			{
				buf += line[x];
			}
			else { break; }	//Break out if unrecognised character
		}
		//Hexadecimal check
		else if (type == n_hex)
		{
			char comp = toupper(line[x]);
			if ((line[x] >= '0' && line[x] <= '9') || (comp >= 'A' && comp <= 'F'))
			{
				buf += line[x];
			}
			else { break; }	//Break out if unrecognised character
		}
		//Binary check
		else if (type == n_bin)
		{
			if (line[x] >= '0' && line[x] <= '1')
			{
				buf += line[x];
			}
			else { break; }	//Break out if unrecognised character
		}
		index++;
	}
	int val = 0;
	switch (type)
	{
	case n_dec:
		val = strtol(buf.c_str(), NULL, 10);
		break;
	case n_hex:
		val = strtol(buf.c_str(), NULL, 16);
		break;
	case n_bin:
		val = strtol(buf.c_str(), NULL, 2);
		break;
	}
	return val;
}

void TokeniseArguments(std::vector<Token>* tokens, std::string args)
{
	Token newtoken;
	std::string buf = "";
	for (int x = 0; x < args.size(); x++)
	{
		newtoken = Token();
		buf += args[x];
		
		//Break out if comment or carridge return found
		if (buf == COMMENT || buf == RETURN) { break; }

		//Clear out unessecary characters
		if (buf == SPACE || buf == TAB) { buf = "";  continue; }

		//Register checking
		for (int y = 0; y < z80_reg_len; y++)
		{
			if (buf == Z80_register_ident[y])
			{
				//Registers are always ended by either a return or seperator character
				if (args[fmin(x, args.size()) + 1] == TOKEN_SEPERATOR || args[fmin(x, args.size()) + 1] == TOKEN_BCLOSE)
				{
					newtoken.type = t_Z80_reg;
					newtoken.value = y;
					tokens->push_back(newtoken);
					buf = "";
					break;
				}
			}
		}
		//Number checking
		if (buf[0] >= '0' && buf[0] <= '9') //Decimal
		{
			newtoken.type = t_number;
			newtoken.value = ReadNumber(args, x, n_dec);
			tokens->push_back(newtoken);
			buf = "";
		}

		//Single pass checks
		switch (buf[0])
		{
		case TOKEN_HEX:
			x++;											//Skip current character for proper digit reading
			newtoken.type = t_number;
			newtoken.value = ReadNumber(args, x, n_hex);
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_BIN:
			x++;											//Skip current character for proper digit reading
			newtoken.type = t_number;
			newtoken.value = ReadNumber(args, x, n_bin);
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_IMM:
			newtoken.type = t_imm;
			newtoken.value = 0;
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_BOPEN:
			newtoken.type = t_bropen;
			newtoken.value = 0;
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_BCLOSE:
			newtoken.type = t_brclose;
			newtoken.value = 0;
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_SEPERATOR:
			newtoken.type = t_seperator;
			newtoken.value = 0;
			tokens->push_back(newtoken);
			buf = "";
			break;
		case TOKEN_ADD:
			newtoken.type = t_add;
			newtoken.value = 0;
			tokens->push_back(newtoken);
			buf = "";
			break;
		}
	}
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