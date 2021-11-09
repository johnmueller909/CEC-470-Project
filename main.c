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
  unsigned int MAR=0;
  unsigned int PC=0;

  int main(int argc, char* argv[])
  {
    
		/* READ FROM FILE AND LOAD INTO MEMORY HERE */
		
		/*execution loop. continue fetching and executing until PC points to a
    HALT instruction*/
    while(memory[PC] != HALT_OPCODE)
    {
      fetchNextInstruction();
      executeInstruction();
    }
    return 0;
  }
	
	void fetchNextInstruction()
	{
		// IR = next opcode
		IR = memory[PC];
		
		// checking opcode
		if((IR & 0x80) == 0x80) /* Mathematical Operation */
		{
			/* if first bit is 1, mathematical operation */
			
			/* JOHN PC INCREMENT CODE HERE */
			
		} else if ((IR & 0xf0) == 0) { /* Memory operation */
			// if first 4 bits are 0000, memory operation
			
			/* SUMMER PC INCREMENT CODE HERE */
			
			switch(IR & 0x0F)
			{

				case 0x00: // 0000 0000
					// store ACC [16-bit address]
					PC += 3;
					break;
				
				case 0x01: // 0000 0001
					// store ACC (8-bit constant)
					PC += 2;
					break;
				
				case 0x02: // 0000 0010
					// store ACC [MAR] | MAR is 16-bit address
					PC++;
					break;
				
				case 0x04: // 0000 0100
					//store MAR [16-bit address]
					PC += 3;
					break;
				
				case 0x05: // 0000 0101
					// store MAR (16-bit constant)
					PC += 3;
					break;
				
			}
			
		} else if ((IR & 0xF8) == 0x10) { /* Branch/Jump */
			// if first 5 bits are 00010, branch/jump operation
			
			/* SARAH PC INCREMENT CODE HERE */
			
		} else { /* Special Opcode */
			// else its a special opcode
			
		}		
		
		
	}
	
	void executeInstruction()
	{
		
		// checking opcode
		if((IR & 0x80) == 0x80) /* Mathematical Operation */
		{
			/* if first bit is 1, mathematical operation */
			
			/* JOHN INSTRUCTION CODE HERE */
			
		} else if ((IR & 0xf0) == 0) { /* Memory operation */
			// if first 4 bits are 0000, memory operation
			
			/* SUMMER INSTRUCTION CODE HERE */
			
		} else if ((IR & 0xF8) == 0x10) { /* Branch/Jump */
			// if first 5 bits are 00010, branch/jump operation
			
			/* SARAH INSTRUCTION CODE HERE */
			
		} else { /* Special Opcode */
			// else its a special opcode
			
		}	
		
	}
	
	
	

	
	
	
	
