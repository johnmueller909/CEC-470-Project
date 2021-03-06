#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HALT_OPCODE 0x19

void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC=0;
unsigned char IR=0;
unsigned int MAR=0;
unsigned int PC=0;

void executeInstruction()
	{
		// checking opcode
		if ((IR & 0x80) == 0x80) /* Mathematical Operation */
		{
			/* JOHN INSTRUCTION CODE HERE */
			int D; //D for destination
			int S; // S for source

			switch (IR & 0x0c) { // This is to check destination

			case 0: // Indirect (MAR as pointer)
				D = memory[MAR];
				break;

			case 4: // Accumulator ACC
				D = ACC;
				break;

			case 8: // Address register MAR
				D = MAR;
				break;

			case 12: // Memory
				if ((IR & 0x02) == 0)
					D = memory[((memory[PC - 2] << 8) + memory[PC - 1])];
				else
					D = memory[((memory[PC - 4] << 8) + memory[PC - 3])];
				break;
			}

			switch (IR & 0x03) { // This is to check the source

			case 0: // Indirect (MAR used as a pointer)
				S = memory[MAR];
				break;

			case 1: // Accumulator ACC
				S = ACC;
				break;

			case 2: // Constant
				S = memory[PC - 1];
				if ((IR & 0x0c) == 0x8)
					S += memory[PC - 2] << 8;
				break;

			case 3: // Memory
				S = memory[((memory[PC - 2] << 8) + memory[PC - 1])];
				if ((IR & 0x0c) == 0x8) {
					S <<= 8;
					S += memory[(memory[PC - 2] << 8) + memory[PC - 1] + 1];
				}
				break;
			}

			switch (IR & 0x70) { // Checking which function

			case 0x00: // AND operation
				D &= S;
				break;
			case 0x10: // OR opertaion
				D |= S;
				break;
			case 0x20: // XOR operation
				D ^= S;
				break;
			case 0x30: // ADD operation
				D += S;
				break;
			case 0x40: // SUB operation
				D -= S;
				break;
			case 0x50: // INC operation
				D++;
				break;
			case 0x60: // DEC operation
				D--;
				break;
			case 0x70: // NOT operation
				D = !D;
				break;
			}

			switch (IR & 0x0c) { // Checks the store destination

			case 0x0: // Indirect (MAR used as pointer)
				memory[MAR] = D & 0xff;
				break;

			case 0x4: // Accumulator ACC
				ACC = D & 0xff;
				break;

			case 0x8: // Address register MAR
				MAR = D & 0xffff;
				break;

			}
		}
		else if ((IR & 0xF8) == 0x10) { /* Branch/Jump */
		 // if first 5 bits are 00010, branch/jump operation
		 /* SARAH INSTRUCTION CODE HERE */
			switch (IR & 0x0F)
			{
			case 0x00: //000
				PC = (memory[PC - 1] << 8) + memory[PC - 2];
				break;

			case 0x01: //001
				if (ACC == 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			case 0x02: //010
				if (ACC != 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			case 0x03: //011
				if (ACC < 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			case 0x04: //100
				if (ACC <= 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			case 0x05: //101
				if (ACC > 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			case 0x06: //110
				if (ACC >= 0)
				{
					PC = (memory[PC - 1] << 8) + memory[PC - 2];
				}
				break;

			}
		}
		else if ((IR & 0xF0) == 0) { /* Memory operation */
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


	}
