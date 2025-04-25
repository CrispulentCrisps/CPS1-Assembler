#pragma once
#include "Types.h"

extern FILE* input;							    //Input file
extern FILE* output;						    //Output file

extern std::vector<VariableDef> variables;      //Variables list
extern std::vector<LabelDef> labels;            //Label list
extern std::vector<std::string> codelines;      //List of code lines
extern std::vector<Z80Opcode> Z80OpList;	    //List of Z80 commands
extern std::vector<M68KOpcode> M68KOpList;	    //List of M68K commands
extern arch_type arch;						    //Current architecture type

void ParseLines();

//Z80
int Interpret_Z80();						    //Run through and identify Z80 code
int DetermineCommand_Z80(std::string com);	    //Determine if current command is a Z80 command
void HandleComType_Z80(int comind, int lineind);//Determine which command function to execute

//Command bvytecode determination
Z80Opcode Determine_LD();                       //Determine what type of loading to do

//Z80 code generation
int Generate_Z80();							    //Generate Z80 bytecode in output file

//M68K
int Interpret_M68K();						    //Run through and identify Z80 code
int Generate_M68K();						    //Generate M68K bytecode in output file

//General assembler
arch_type DetermineArch();					    //Determine current architecture in file
LabelDef AddLabel(std::string name);
int DetermineAssemblerCommand(std::string com); //Determine if the current command is a 

bool OpenFile(int argc, char** argv);           //Open input and output files if passesed
