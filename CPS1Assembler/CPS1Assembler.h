//Header file for CPS1Assembler

#pragma once
#include "Z80.h"

//|---------------------|
//|	Assembler variables	|
//|---------------------|
extern FILE* input;										                //Input file
extern FILE* output;									                //Output file

//|-----------------------------|
//|	General assembler functions	|
//|-----------------------------|
void ParseLines();										                //Read code from text file and split into lines
arch_type DetermineArch();								                //Determine current architecture in file
LabelDef AddLabel(std::string name);					                //Create label instance
int DetermineAssemblerCommand(std::string com);			                //Determine if the current command is a 
int ReadNumber(std::string line, int& index, num_type type);            //Read line from index to end and return string of read number chars
void TokeniseArguments(std::vector<Token>* tokens, std::string args);   //Passes through argument list and tkenises based off of argument

bool OpenFile(int argc, char** argv);					                //Open input and output files if passesed
