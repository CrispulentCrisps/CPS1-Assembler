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

arch_type DetermineArch()
{
	for (int x = 0; x < codelines.size(); x++)
	{
		if (codelines[x] == ex_keyword_ident[arch_Z80])
		{
			return Z80;
		}
		else if (codelines[x] == ex_keyword_ident[arch_M68K])
		{
			return M68K;
		}
	}
	return NOARCH;
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
			//Clear linebuf if these characters found
			if (linebuf == TAB || linebuf == RETURN || linebuf == SPACE) { linebuf = ""; }
			//Skip line read if current line is a comment
			else if (linebuf == TAB) { break; }

			//If a usable command has been found
			if (DetermineCommandZ80(linebuf) != COM_NULL) 
			{

			}

			//Otherwise continue reading
		}
	}
	return Z80_FINE;
}

//Determine if current command is a Z80 command
int DetermineCommandZ80(std::string com)
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