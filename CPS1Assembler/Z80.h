#pragma once
#include "Types.h"

//|-----------------------------|
//|	  Z80 assembler functions	|
//|-----------------------------|
int Interpret_Z80();									                    //Run through and identify Z80 code
int DetermineCommand_Z80(std::string com);				                    //Determine if current command is a Z80 command
void HandleComType_Z80(int comind, int lineind);		                    //Determine which command function to execute
std::string GetInstructionArgs_Z80(int comind, std::string line);	        //Returns the string of characters after the opcode type

//Instruction type determination
ComLine Determine_LD   (std::vector<Token>* tokens);	//Returns command for load instruction
ComLine Determine_PUSH (std::vector<Token>* tokens);	//
ComLine Determine_POP  (std::vector<Token>* tokens);	//
ComLine Determine_EX   (std::vector<Token>* tokens);	//
ComLine Determine_EXX  (std::vector<Token>* tokens);	//
ComLine Determine_LDI  (std::vector<Token>* tokens);	//
ComLine Determine_LDIR (std::vector<Token>* tokens);	//
ComLine Determine_LDD  (std::vector<Token>* tokens);	//
ComLine Determine_LDDR (std::vector<Token>* tokens);	//
ComLine Determine_CPI  (std::vector<Token>* tokens);	//
ComLine Determine_CPIR (std::vector<Token>* tokens);	//
ComLine Determine_CPD  (std::vector<Token>* tokens);	//
ComLine Determine_CPDR (std::vector<Token>* tokens);	//
ComLine Determine_ADD  (std::vector<Token>* tokens);	//
ComLine Determine_ADC  (std::vector<Token>* tokens);	//
ComLine Determine_SUB  (std::vector<Token>* tokens);	//
ComLine Determine_SBC  (std::vector<Token>* tokens);	//
ComLine Determine_AND  (std::vector<Token>* tokens);	//
ComLine Determine_OR   (std::vector<Token>* tokens);	//
ComLine Determine_XOR  (std::vector<Token>* tokens);	//
ComLine Determine_CP   (std::vector<Token>* tokens);	//
ComLine Determine_INC  (std::vector<Token>* tokens);	//
ComLine Determine_DEC  (std::vector<Token>* tokens);	//
ComLine Determine_DAA  (std::vector<Token>* tokens);	//
ComLine Determine_CPL  (std::vector<Token>* tokens);	//
ComLine Determine_NEG  (std::vector<Token>* tokens);	//
ComLine Determine_CCF  (std::vector<Token>* tokens);	//
ComLine Determine_SCF  (std::vector<Token>* tokens);	//
ComLine Determine_RCLA (std::vector<Token>* tokens);	//
ComLine Determine_RLA  (std::vector<Token>* tokens);	//
ComLine Determine_RRCA (std::vector<Token>* tokens);	//
ComLine Determine_RRA  (std::vector<Token>* tokens);	//
ComLine Determine_RL   (std::vector<Token>* tokens);	//
ComLine Determine_RR   (std::vector<Token>* tokens);	//
ComLine Determine_SLA  (std::vector<Token>* tokens);	//
ComLine Determine_SLR  (std::vector<Token>* tokens);	//
ComLine Determine_RLD  (std::vector<Token>* tokens);	//
ComLine Determine_RRD  (std::vector<Token>* tokens);	//
ComLine Determine_BIT  (std::vector<Token>* tokens);	//
ComLine Determine_SET  (std::vector<Token>* tokens);	//
ComLine Determine_RES  (std::vector<Token>* tokens);	//
ComLine Determine_JP   (std::vector<Token>* tokens);	//
ComLine Determine_JR   (std::vector<Token>* tokens);	//
ComLine Determine_DJNZ (std::vector<Token>* tokens);	//
ComLine Determine_CALL (std::vector<Token>* tokens);	//
ComLine Determine_RET  (std::vector<Token>* tokens);	//
ComLine Determine_RETI (std::vector<Token>* tokens);	//
ComLine Determine_RETN (std::vector<Token>* tokens);	//
ComLine Determine_RST  (std::vector<Token>* tokens);	//
ComLine Determine_IN   (std::vector<Token>* tokens);	//
ComLine Determine_INI  (std::vector<Token>* tokens);	//
ComLine Determine_IND  (std::vector<Token>* tokens);	//
ComLine Determine_INDR (std::vector<Token>* tokens);	//
ComLine Determine_OUT  (std::vector<Token>* tokens);	//
ComLine Determine_OTIR (std::vector<Token>* tokens);	//
ComLine Determine_OUTD (std::vector<Token>* tokens);	//
ComLine Determine_OTDR (std::vector<Token>* tokens);	//

//Code generation
int Generate_Z80();										//Generate Z80 bytecode in output file

extern TokenTableEntry LDList[132];