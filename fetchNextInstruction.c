#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HALT_OPCODE 0x19

void fetchNextInstruction(void);

unsigned char memory[65536];
unsigned char ACC=0;
unsigned char IR=0;
unsigned int MAR=0;
unsigned int PC=0;

void fetchNextInstruction()
	{
		// IR = next opcode
		IR = memory[PC];

		// checking opcode
		if((IR & 0x80) == 0x80) /* Mathematical Operation */
		{
	          /* JOHN PC INCREMENT CODE HERE */
	          if ((IR & 0x0c) == 0x0c){ // If the destination is memory
				  PC += 2;
	         }
	            switch (IR & 0x03) { // For the source

                    case 3: // If the source is a constant
                      if ((IR & 0x08) == 0x08) // This is for 16-bit destination
                          PC++;
                          PC++;
                          break;

                    case 4: // If the source is a memory location
                          PC += 2;
						  break;
                }

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

            		PC = PC + 3;

		} else { /* Special Opcode */
			// else its a special opcode
			PC++;
		    // The following is the logic code for a special opcode or an illegal opcode
		    if (IR == 0x18) // Then it's a NOP -- do nothing
		    {

		    }
		    else if (IR == 0x19) // Then it's a HALT -- framework will halt for us
		    {
			HALT_OPCODE;
		    }
		    else { // Otherwise it's an illegal opcode -- you can print an error message if you want to
		    }
		}


	}
