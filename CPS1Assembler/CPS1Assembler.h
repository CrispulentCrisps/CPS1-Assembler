//Header file for CPS1Assembler

#pragma once
#include "Types.h"

//|---------------------|
//|	Assembler variables	|
//|---------------------|
extern FILE* input;										//Input file
extern FILE* output;									//Output file

extern std::vector<VariableDef> Variables;				//Variables list
extern std::vector<LabelDef> Labels;					//Label list
extern std::vector<std::string> CodeLines;				//List of code lines
extern std::vector<ComLine> ComList;					//List of parsed commands
extern arch_type arch;									//Current architecture type



//|-----------------------------|
//|	  Z80 assembler functions	|
//|-----------------------------|
int Interpret_Z80();									//Run through and identify Z80 code
int DetermineCommand_Z80(std::string com);				//Determine if current command is a Z80 command
void HandleComType_Z80(int comind, int lineind);		//Determine which command function to execute

//Instruction type determination
void Determine_LD(ComLine* com, std::string line);		//
void Determine_PUSH(ComLine* com, std::string line);	//
void Determine_POP(ComLine* com, std::string line);		//
void Determine_EX(ComLine* com, std::string line);		//
void Determine_EXX(ComLine* com, std::string line);		//
void Determine_LDI(ComLine* com, std::string line);		//
void Determine_LDIR(ComLine* com, std::string line);	//
void Determine_LDD(ComLine* com, std::string line);		//
void Determine_LDDR(ComLine* com, std::string line);	//
void Determine_CPI(ComLine* com, std::string line);		//
void Determine_CPIR(ComLine* com, std::string line);	//
void Determine_CPD(ComLine* com, std::string line);		//
void Determine_CPDR(ComLine* com, std::string line);	//
void Determine_ADD(ComLine* com, std::string line);		//
void Determine_ADC(ComLine* com, std::string line);		//
void Determine_SUB(ComLine* com, std::string line);		//
void Determine_SBC(ComLine* com, std::string line);		//
void Determine_AND(ComLine* com, std::string line);		//
void Determine_OR(ComLine* com, std::string line);		//
void Determine_XOR(ComLine* com, std::string line);		//
void Determine_CP(ComLine* com, std::string line);		//
void Determine_INC(ComLine* com, std::string line);		//
void Determine_DEC(ComLine* com, std::string line);		//
void Determine_DAA(ComLine* com, std::string line);		//
void Determine_CPL(ComLine* com, std::string line);		//
void Determine_NEG(ComLine* com, std::string line);		//
void Determine_CCF(ComLine* com, std::string line);		//
void Determine_SCF(ComLine* com, std::string line);		//
void Determine_NOP(ComLine* com, std::string line);		//
void Determine_HALT(ComLine* com, std::string line);	//
void Determine_DI(ComLine* com, std::string line);		//
void Determine_EI(ComLine* com, std::string line);		//
void Determine_IM0(ComLine* com, std::string line);		//
void Determine_IM1(ComLine* com, std::string line);		//
void Determine_IM2(ComLine* com, std::string line);		//
void Determine_RCLA(ComLine* com, std::string line);	//
void Determine_RLA(ComLine* com, std::string line);		//
void Determine_RRCA(ComLine* com, std::string line);	//
void Determine_RRA(ComLine* com, std::string line);		//
void Determine_RL(ComLine* com, std::string line);		//
void Determine_RR(ComLine* com, std::string line);		//
void Determine_SLA(ComLine* com, std::string line);		//
void Determine_SLR(ComLine* com, std::string line);		//
void Determine_RLD(ComLine* com, std::string line);		//
void Determine_RRD(ComLine* com, std::string line);		//
void Determine_BIT(ComLine* com, std::string line);		//
void Determine_SET(ComLine* com, std::string line);		//
void Determine_RES(ComLine* com, std::string line);		//
void Determine_JP(ComLine* com, std::string line);		//
void Determine_JR(ComLine* com, std::string line);		//
void Determine_DJNZ(ComLine* com, std::string line);	//
void Determine_CALL(ComLine* com, std::string line);	//
void Determine_RET(ComLine* com, std::string line);		//
void Determine_RETI(ComLine* com, std::string line);	//
void Determine_RETN(ComLine* com, std::string line);	//
void Determine_RST(ComLine* com, std::string line);		//
void Determine_IN(ComLine* com, std::string line);		//
void Determine_INI(ComLine* com, std::string line);		//
void Determine_IND(ComLine* com, std::string line);		//
void Determine_INDR(ComLine* com, std::string line);	//
void Determine_OUT(ComLine* com, std::string line);		//
void Determine_OTIR(ComLine* com, std::string line);	//
void Determine_OUTD(ComLine* com, std::string line);	//
void Determine_OTDR(ComLine* com, std::string line);	//

//Code generation
int Generate_Z80();										//Generate Z80 bytecode in output file



//|-----------------------------|
//|	  M68K assembler functions	|
//|-----------------------------|
int Interpret_M68K();									//Run through and identify Z80 code
int Generate_M68K();									//Generate M68K bytecode in output file



//|-----------------------------|
//|	General assembler functions	|
//|-----------------------------|
void ParseLines();										//Read code from text file and split into lines
arch_type DetermineArch();								//Determine current architecture in file
LabelDef AddLabel(std::string name);					//Create label instance
int DetermineAssemblerCommand(std::string com);			//Determine if the current command is a 
std::string GetInstructionArgs(int lineind);			//Returns the string of characters after the 

bool OpenFile(int argc, char** argv);					//Open input and output files if passesed
