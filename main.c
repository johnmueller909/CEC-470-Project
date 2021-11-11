/*CEC 470  Computer Organization and Architecture
  Instruction Decoder Project
  Submitted by: Sarah Harrington, John-Patrick Mueller, AnnaMaria Summer
  Created: 10/29/21  Last Edited:10/29/21*/

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
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
    FILE *mem; //Creates a file pointer for mem_in.txt
    mem = fopen("mem_in.txt","r"); //Opens mem_in.txt for reading.
    int i;
    
    for (i = 0; i < 65536; i++)
    {
      fscanf(mem, "%d", &memory[i]);
    }
    fclose(mem); //close file mem_in.txt  
	  
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
				case 0x06: // 0000 0110
					// store MAR [MAR] 16-bit address
					PC++;
					break;
				
				case 0x08: // 0000 1000
					// load ACC [16-bit address]
					PC += 3;
					break;
				
				case 0x09: // 0000 1001
					// load ACC (16-bit constant)
					PC += 3;
					break;
				
				case 0x0A: // 0000 1010
					// load ACC [MAR] | 16-bit address
					PC++;
					break;
				
				case 0x0C: // 0000 1100
					// load MAR [16-bit address]
					PC += 3;
					break;
				
				case 0x0D: // 0000 1101
					// load MAR (16-bit constant)
					PC += 3;
					break;
				
				case 0x0E: // 0000 1110
					// load MAR [MAR] | 16-bit address
					PC++;
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
			
		} else if ((IR & 0xF0) == 0) { /* Memory operation */
			// if first 4 bits are 0000, memory operation
			
			/* SUMMER INSTRUCTION CODE HERE */
			
			// executing the instruction
			switch(IR & 0x0F)
			{
				
				case 0x00: // 0000 0000
					// store ACC [16-bit address]
					memory[ (memory[PC-2]<<8) + memory[PC-1] ] = ACC;
					break;
				
				case 0x01: // 0000 0001
					// store ACC (8-bit constant)
					memory[PC-1] = ACC;
					break;
				
				case 0x02: // 0000 0010
					// store ACC [MAR] 
					memory[MAR] = ACC;
					break;
				
				case 0x04: // 0000 0100
					//store MAR [16-bit address]
					memory[ (memory[PC-2] << 8) + memory[PC-1] ] = MAR >> 8;
					memory[ (memory[PC-2] << 8) + memory[PC-1] + 1 ] = MAR - ( (MAR >> 8) << 8);
					break;
				
				case 0x05: // 0000 0101
					// store MAR (16-bit constant)
					memory[ (memory[PC-2] << 8) + memory[PC-1] ] = MAR;
					break;
				
				case 0x06: // 0000 0110
					// store MAR [MAR] 16-bit address
					memory[MAR] = MAR >> 8;
					memory[MAR + 1] = MAR - ((MAR >> 8) <<8);
					break;
				
				case 0x08: // 0000 1000
					// load ACC [16-bit address]
					ACC = memory[ (memory[PC+1]<<8) + memory[PC+2] ];
					break;
				
				case 0x09: // 0000 1001
					// load ACC (8-bit constant)
					ACC = memory[PC-1];
					break;
				
				case 0x0A: // 0000 1010
					// load ACC [MAR] | 16-bit address
					ACC = memory[MAR];
					break;
				
				case 0x0C: // 0000 1100
					// load MAR [16-bit address]
					MAR = ((memory[memory[PC-2]]) << 8) + memory[memory[PC-1]];
					break;
				
				case 0x0D: // 0000 1101
					// load MAR (16-bit constant)
					MAR = (memory[PC-2]<<8) + memory[PC-1];
					break;
				
				case 0x0E: // 0000 1110
					// load MAR [MAR] | 16-bit address
					MAR = memory[(memory[PC-2]<<8) + memory[PC-1]];
					break;
				
			}
			
		} else if ((IR & 0xF8) == 0x10) { /* Branch/Jump */
			// if first 5 bits are 00010, branch/jump operation
			
			/* SARAH INSTRUCTION CODE HERE */
			
		} else { /* Special Opcode */
			// else its a special opcode
			
		}	
		
	}
	
	
	

	
	
	
	
