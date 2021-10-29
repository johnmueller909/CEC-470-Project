/*CEC 470  Computer Organization and Architecture
  Instruction Decoder Project
  Submitted by: Sarah Harrington, John-Patrick Mueller, AnnaMaria Summer
  Created: 10/29/21  Last Edited:10/29/21*/

  #define HALT_OPCODE 0x19

  void fetchNextInstruction(void);
  void executeInstruction(void);

  unsigned char memory[65536];
  unsigned char ACC=0;
  unsigned char IR=0;
  unsiged int MAR=0;
  unsigned int PC=0;

  int main(int argc, CHAR* argv[])
  {
    /*execution loop. continue fetching and executing until PC points to a
    HALT instruction*/
    while(memory[PC] != HALT_OPCODE)
    {
      fetchNextInstruction();
      executeInstruction();
    }
    return 0;
  }
