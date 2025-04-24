// CPS1Assembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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

int main(int argc, char** argv)
{
	//Opening source file
	if (!OpenFile(argc, argv)) {
		std::cout << "\n\nERROR, ASSEMBLER FAILURE!";
		return 1;
	}

	variables.clear();
	labels.clear();
	codelines.clear();
	ParseLines();
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

bool OpenFile(int argc, char** argv)
{
	//Check arguments
	for (int i = 0; i < argc; ++i) { std::cout << argv[i] << "\n"; }

	//Check if file is empty
	if (argv[1] == NULL) {
		std::cout << "NO FILENAME GIVEN";
		return false;
	}

	input = fopen(argv[1], "r");
	if (input == NULL)
	{
		char buf[256];
		memcpy(buf, argv[1], strlen(argv[1]));
		std::cout << "ERROR, NO FILE FOUND AT: " << buf;
		return 1;
	}

	//Output file for the target architecture
	output = fopen(argv[2], "wb");

	//Find file size
	fseek(input, 0, SEEK_END);
	int size = ftell(input);
	rewind(input);

	return true;
}