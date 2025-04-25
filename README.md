# CPS1-Assembler
 An assembler that targets the Z80 and Motorola 68000 CPUs

 # Use
 The program expects **1** source file and **1** output file, respectively

 so for example
 `
 CPS1Assembler.exe source1.asm output1.bin
 `
 will take in source1 and assemble it into output1.bin

 # TO-DO
 - Code generation
    - Start Z80 code generation
    - Handle variables
    - Handle labels
    - Add bytecode generation table
    
 - Code parsing
    - make incsrc functional
    - make incbin functional
    - make org functional
    - Determine address width based off of variable value
    - Recognise different number bases
    - Recognise instructions and registers