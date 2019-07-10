// Name-: Brian Wittel
// NID--: br933378
// Date-: 2018/04/20
// Class: CDA 3103
// Program: MySPIM

#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    //Check if A and B are equal
    if((A-B) == 0) {
        *Zero = 1;
    } else {
        *Zero = 0;
    }
    //ALUControl Logic
    // A+B
    if(ALUControl == 0x0) {
        *ALUresult = A+B;
    // A-B
    } else if(ALUControl == 0x1) {
        *ALUresult = A-B;
    // A<B -> Z=1 Otherwise Z=0
    } else if(ALUControl == 0x2) {
        if(!(A & (1<<31)) && !(B & (1<<31))) {
            if(A < B) {
                *ALUresult = 1;
            } else {
                *ALUresult = 0;
            }
        } else if((A & (1<<31)) && (B & (1<<31))) {
            if(A > B) {
                *ALUresult = 1;
            } else {
                *ALUresult = 0;
            }
        } else if((A & (1<<31)) && !(B & (1<<31))) {
            *ALUresult = 0;
        } else {
            *ALUresult = 1;
        }
    // If A<B -> Z=1 Otherwise Z=0 (A and B are unsigned ints)
    } else if(ALUControl == 0x3) {
        if(A < B) {
            *ALUresult = 1;
        } else {
            *ALUresult = 0;
        }
    // A&B
    } else if(ALUControl == 0x4) {
        *ALUresult = A & B;
    // A|B
    } else if(ALUControl == 0x5) {
        *ALUresult = A | B;
    // B left shift 16 bits
    } else if(ALUControl == 0x6) {
        *ALUresult = B << 16;
    // Z is Not A
    } else if(ALUControl == 0x7) {
        *ALUresult = ~A;
    // Error message otherwise
    } else {
        printf("\n\n---ERROR - ALU - ALUControl Error!---\n\n");
    }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //Check to see if in proper word-aligned format. If so...
    if(PC%4 == 0) {
        //...set instruction accordingly. If not...
        *instruction = Mem[PC >> 2];
    } else {
        //...halt.
        return 1;
    }
    return 0;
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    //Partitions used to change values accordingly
    unsigned rPart =       0x1f;
    unsigned functOpPart = 0x0000003f;
    unsigned offsetPart =  0x0000ffff;
    unsigned jsecPart =    0x03ffffff;
    //Instructions with partitions and shifts
    *op =     (instruction >> 26) & functOpPart; //Instruction [31-26]
    *r1 =     (instruction >> 21) & rPart;       //Instruction [25-21]
    *r2 =     (instruction >> 16) & rPart;       //Instruction [20-16]
    *r3 =     (instruction >> 11) & rPart;       //Instruction [15-11]
    *funct =   instruction & functOpPart;        //Instruction [05-00]
    *offset =  instruction & offsetPart;         //Instruction [15-00]
    *jsec =    instruction & jsecPart;           //Instruction [25-00]
}

/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    //struct_controls format -
    //    {RegDst, Jump, Branch, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite}

    //ADD, SUB, AND, OR, SLT, SLTU
    if(op == 0x0) {
        *controls = (struct_controls) {1,0,0,0,0,7,0,0,1};
    //ADDI
    } else if(op == 0x8) {
        *controls = (struct_controls) {0,0,0,0,0,0,0,1,1};
    //LW
    } else if(op == 0x23) {
        *controls = (struct_controls) {0,0,0,1,1,0,0,1,1};
    //SW
    } else if(op == 0x2b) {
        *controls = (struct_controls) {0,0,0,0,0,0,1,1,0};
    //LUI
    } else if(op == 0xf) {
        *controls = (struct_controls) {0,0,0,0,0,6,0,1,1};
    //BEQ
    } else if(op == 0x4) {
        *controls = (struct_controls) {2,0,1,0,2,1,0,2,0};
    //SLTI
    } else if(op == 0xa) {
        *controls = (struct_controls) {0,0,0,0,0,2,0,1,1};
    //SLTIU
    } else if(op == 0xb) {
        *controls = (struct_controls) {0,0,0,0,0,3,0,1,1};
    //J
    } else if(op == 0x2) {
        *controls = (struct_controls) {2,1,2,0,2,0,0,2,0};
    //halt
    } else {
        return 1;
    }
    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1]; //Content from Register at r1
    *data2 = Reg[r2]; //Content from Register at r2
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    //Check to see if offset bit is negative or positive. If negative...
    if((offset>>15) == 1) {
        //...make last 16 bits 1s to maintain negative. Otherwise...
        *extended_value = offset | 0xffff0000;
    } else {
        //...make the last 16 bits keep positive value.
        *extended_value = offset & 0x0000ffff;
    }

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    //Creates mirror of ALUOp
    unsigned char ALUC = ALUOp;
    //Operation Logic
    //If R-Type instruction...
    if(ALUOp == 0x7) {
        //...check if ADD...
        if(funct == 0x20) {
            ALUC = 0x0;
        //...AND...
        } else if(funct == 0x24) {
            ALUC = 0x4;
        //...OR...
        } else if(funct == 0x25) {
            ALUC = 0x5;
        //...SLT...
        } else if(funct == 0x2a) {
            ALUC = 0x2;
        //...SLTU...
        } else if(funct == 0x2b) {
            ALUC = 0x3;
        //...or halt.
        } else {
            return 1;
        }
    //If not R-Type instruction (ADD/Don't Care, SUB, SLT, SLTU, AND, OR, SHIFT) do nothing. Otherwise...
    } else if(ALUOp == 0X0 || ALUOp == 0X1 || ALUOp == 0X2 || ALUOp == 0X3 || ALUOp == 0X4 || ALUOp == 0X5 || ALUOp == 0X6){
        ;
    //...halt.
    } else {
        return 1;
    }
    //ALU is called with B variable depending on the result of ternary operator (ALUSrc).
    if(ALUSrc == 1) {
        //B = extended_value
        ALU(data1, extended_value, ALUC, ALUresult, Zero);
    } else {
        //B = data2
        ALU(data1, data2, ALUC, ALUresult, Zero);
    }
    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    //If reading from memory
    if(MemRead == 1) {
        if(ALUresult%4 == 0 && ALUresult < 65536) {
            *memdata = Mem[ALUresult >> 2];
        } else {
            return 1;
        }
    }
    //If writing to memory
    if(MemWrite == 1) {
        if(ALUresult%4 == 0 && ALUresult < 65536) {
            Mem[ALUresult >> 2] = data2;
        } else {
            return 1;
        }
    }
    return 0;
}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    //If writing...
    if(RegWrite == 1) {
        //...and if its origin is memory...
        if(MemtoReg == 1) {
            //...then add to r2. Otherwise...
            Reg[r2] = memdata;
        } else if(MemtoReg == 0) {
            //...check to see if instruction is R-Type. If so...
            if(RegDst == 1) {
                //...write to r3. Otherwise...
                Reg[r3] = ALUresult;
            } else {
                //...off to r2 with you!
                Reg[r2] = ALUresult;
            }
        }
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    //Increment the PC by 4
    *PC += 4;
    //If branching and zero are true we add extended value
    if(Zero == 1 && Branch == 1) {
        *PC = *PC + (extended_value << 2);
    }
    //If jump is true combine with PC and shift instruction
    if(Jump == 1) {
        *PC = (*PC & 0xf00000000) | (jsec << 2);
    }
}
