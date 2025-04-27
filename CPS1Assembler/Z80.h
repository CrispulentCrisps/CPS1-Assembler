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
void Determine_LD   (std::vector<Token>* tokens);	//
void Determine_PUSH (std::vector<Token>* tokens);	//
void Determine_POP  (std::vector<Token>* tokens);	//
void Determine_EX   (std::vector<Token>* tokens);	//
void Determine_EXX  (std::vector<Token>* tokens);	//
void Determine_LDI  (std::vector<Token>* tokens);	//
void Determine_LDIR (std::vector<Token>* tokens);	//
void Determine_LDD  (std::vector<Token>* tokens);	//
void Determine_LDDR (std::vector<Token>* tokens);	//
void Determine_CPI  (std::vector<Token>* tokens);	//
void Determine_CPIR (std::vector<Token>* tokens);	//
void Determine_CPD  (std::vector<Token>* tokens);	//
void Determine_CPDR (std::vector<Token>* tokens);	//
void Determine_ADD  (std::vector<Token>* tokens);	//
void Determine_ADC  (std::vector<Token>* tokens);	//
void Determine_SUB  (std::vector<Token>* tokens);	//
void Determine_SBC  (std::vector<Token>* tokens);	//
void Determine_AND  (std::vector<Token>* tokens);	//
void Determine_OR   (std::vector<Token>* tokens);	//
void Determine_XOR  (std::vector<Token>* tokens);	//
void Determine_CP   (std::vector<Token>* tokens);	//
void Determine_INC  (std::vector<Token>* tokens);	//
void Determine_DEC  (std::vector<Token>* tokens);	//
void Determine_DAA  (std::vector<Token>* tokens);	//
void Determine_CPL  (std::vector<Token>* tokens);	//
void Determine_NEG  (std::vector<Token>* tokens);	//
void Determine_CCF  (std::vector<Token>* tokens);	//
void Determine_SCF  (std::vector<Token>* tokens);	//
void Determine_NOP  (std::vector<Token>* tokens);	//
void Determine_HALT (std::vector<Token>* tokens);	//
void Determine_DI   (std::vector<Token>* tokens);	//
void Determine_EI   (std::vector<Token>* tokens);	//
void Determine_IM0  (std::vector<Token>* tokens);	//
void Determine_IM1  (std::vector<Token>* tokens);	//
void Determine_IM2  (std::vector<Token>* tokens);	//
void Determine_RCLA (std::vector<Token>* tokens);	//
void Determine_RLA  (std::vector<Token>* tokens);	//
void Determine_RRCA (std::vector<Token>* tokens);	//
void Determine_RRA  (std::vector<Token>* tokens);	//
void Determine_RL   (std::vector<Token>* tokens);	//
void Determine_RR   (std::vector<Token>* tokens);	//
void Determine_SLA  (std::vector<Token>* tokens);	//
void Determine_SLR  (std::vector<Token>* tokens);	//
void Determine_RLD  (std::vector<Token>* tokens);	//
void Determine_RRD  (std::vector<Token>* tokens);	//
void Determine_BIT  (std::vector<Token>* tokens);	//
void Determine_SET  (std::vector<Token>* tokens);	//
void Determine_RES  (std::vector<Token>* tokens);	//
void Determine_JP   (std::vector<Token>* tokens);	//
void Determine_JR   (std::vector<Token>* tokens);	//
void Determine_DJNZ (std::vector<Token>* tokens);	//
void Determine_CALL (std::vector<Token>* tokens);	//
void Determine_RET  (std::vector<Token>* tokens);	//
void Determine_RETI (std::vector<Token>* tokens);	//
void Determine_RETN (std::vector<Token>* tokens);	//
void Determine_RST  (std::vector<Token>* tokens);	//
void Determine_IN   (std::vector<Token>* tokens);	//
void Determine_INI  (std::vector<Token>* tokens);	//
void Determine_IND  (std::vector<Token>* tokens);	//
void Determine_INDR (std::vector<Token>* tokens);	//
void Determine_OUT  (std::vector<Token>* tokens);	//
void Determine_OTIR (std::vector<Token>* tokens);	//
void Determine_OUTD (std::vector<Token>* tokens);	//
void Determine_OTDR (std::vector<Token>* tokens);	//

//Code generation
int Generate_Z80();										//Generate Z80 bytecode in output file

