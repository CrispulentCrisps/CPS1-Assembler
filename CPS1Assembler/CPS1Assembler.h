#pragma once
#include "Types.h"

extern FILE* input;     //Input file
extern FILE* output;    //Output file

extern std::vector<VariableDef> variables;  //Variables list
extern std::vector<LabelDef> labels;        //Label list
extern std::vector<std::string> codelines;  //List of code lines

void ParseLines();

bool OpenFile(int argc, char** argv);        //Open input and output files if passesed