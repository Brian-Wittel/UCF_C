/*
 * University of Central Florida
 * CIS 3360 - Fall 2017
 * Author: Brian Wittel
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void ConvertHtoB(char, char[4]);
void HeaderPrint();
int XORFunC(char[], char[], int);
int XORFunV(char[], char[], int);
char ConvertBtoH(char, char, char, char);

int main(int argc, char *InputH[]){
    //Variables
    char MoO, temp;
    int HSL=0,j=0, BSL, z, CRC, F1=0, CheckA=0;
    char PolyInput[13]={'1','1','0','0','1','1','0','1','1','0','1','0','1'};
    char InputB[172];
    char TempH[4];
    char CRCEnd[12];
    char InputHT[200];
    //Determines the length of the given HEX string
    while(j==0){
        if(InputH[2][HSL]==0){
            j=1;
        }else{
            HSL++;
        }
    }
    //Sets the Mode of Operation to a recognizable variable
    MoO = InputH[1][0];
    //If the given MoO is not one of the prescribed modes then the program gracefully exits
    if(MoO!='c' && MoO!='v'){
        printf("---Incorrect Mode of Operation!---");
        return(1);
    }
    //Check for the user entering enough HEX Characters
    if(HSL<3){
        printf("---Not Enough HEX Characters---");
        return(1);
    //Check if the user entered too many HEX
    }else if(HSL>40){
        printf("---Too Many HEX Characters---");
        return(1);
    }
    //Creates a usable variable related to the amount of HEX given
    BSL=(HSL*4)+12;
    //Prints header and information regardless of mode selected
    HeaderPrint();
    printf("The input string (hex): ");
    //Prints out HEX given
    for(z=0; z<HSL; z++){
        printf("%c", InputH[2][z]);
    }
    printf("\nThe input string (bin): ");
    //Converts input HEX into a binary array
    for(z=0; z<HSL; z++){
        ConvertHtoB(InputH[2][z], TempH);
        InputB[(z*4)+0]=TempH[0];
        InputB[(z*4)+1]=TempH[1];
        InputB[(z*4)+2]=TempH[2];
        InputB[(z*4)+3]=TempH[3];
        //Prints to user with each iteration
        printf("%c%c%c%c ", TempH[0], TempH[1] ,TempH[2], TempH[3]);
    }
    if(MoO=='c'){
        //Creates the pad for CRC-12 at the end of the given HEX
        for(z=0; z<12; z++){
            InputB[(BSL-12+z)]='0';
        }
    }else{
        //Secondary HEX conversion for verification mode save for the last three HEX
        for(z=0; z<HSL-3; z++){
            ConvertHtoB(InputH[2][z], TempH);
            InputHT[(z*4)+0]=TempH[0];
            InputHT[(z*4)+1]=TempH[1];
            InputHT[(z*4)+2]=TempH[2];
            InputHT[(z*4)+3]=TempH[3];
        }
        //Adds the pad to the end of the given HEX minus suspected CRC
        for(z=0; z<12; z++){
            InputHT[(HSL*4)-12+z]='0';
        }
    }
    //Prints polynomial used for this CRC-12
    printf("\n\nThe polynomial used (binary bit string): ");
    for(z=0; z<3; z++){
        printf("%c%c%c%c ", PolyInput[(z*4)+0], PolyInput[(z*4)+1], PolyInput[(z*4)+2], PolyInput[(z*4)+3]);
    }
    printf("%c\n\nMode of operation: ", PolyInput[12]);
    //Calculation Mode
    if(MoO=='c'){
        printf("calculation\n\nNumber of zeroes that will be appended to the binary input: 12\n\nThe binary string difference after each XOR step of the CRC calculation:\n\n");
        //Prints first line to user
        for(z=0; z<(BSL/4); z++){
            printf("%c%c%c%c ", InputB[(z*4)+0], InputB[(z*4)+1], InputB[(z*4)+2], InputB[(z*4)+3]);
        } printf("\n");
        //Runs in this while loop XORing with Input and Poly until reaching a point where it no longer can
        while(F1==0){
            //XORFunC has built in printf to the user
            F1=XORFunC(InputB, PolyInput, BSL);
        }
        printf("\nThe CRC computed from the input: ");
        //Prints the calculated CRC to user in Binary
        for(z=0; z<3; z++){
            printf("%c%c%c%c ", InputB[(BSL-12)+(z*4)+0], InputB[(BSL-12)+(z*4)+1], InputB[(BSL-12)+(z*4)+2], InputB[(BSL-12)+(z*4)+3]);
        } printf("(bin) = ");
        //Prints CRC in HEX
        for(z=0; z<3; z++){
            temp=ConvertBtoH(InputB[(BSL-12)+(z*4)+0], InputB[(BSL-12)+(z*4)+1], InputB[(BSL-12)+(z*4)+2], InputB[(BSL-12)+(z*4)+3]);
            printf("%c", temp);
        } printf(" (hex)\n");
    //Verification Mode
    }else{
        printf("verification\n\nThe CRC observed at the end of the input: ");
        CRC=(HSL-3)*4;
        //Takes the last three HEX to display to the user what is given
        for (z=0; z<3; z++){
            CRCEnd[(z*4)+0]=InputB[CRC+(z*4)+0];
            CRCEnd[(z*4)+1]=InputB[CRC+(z*4)+1];
            CRCEnd[(z*4)+2]=InputB[CRC+(z*4)+2];
            CRCEnd[(z*4)+3]=InputB[CRC+(z*4)+3];
        }
        for(z=0; z<3; z++){
            printf("%c%c%c%c ", CRCEnd[(z*4)+0], CRCEnd[(z*4)+1], CRCEnd[(z*4)+2], CRCEnd[(z*4)+3]);
        }
        printf("(bin) = %c%c%c (hex)\n\nThe binary string difference after each XOR step of the CRC calculation:\n\n", InputH[2][HSL-3], InputH[2][HSL-2], InputH[2][HSL-1]);
        for(z=0; z<(HSL); z++){
            printf("%c%c%c%c ", InputB[(z*4)+0], InputB[(z*4)+1], InputB[(z*4)+2], InputB[(z*4)+3]);
        } printf("\n");
        //XORFunV runs the secondary hidden array through to calculate the CRC with given HEX
        while(F1==0){
            F1=XORFunV(InputHT, PolyInput, (HSL*4));
        } F1=0;
        //XORFunC is mainly used here to output to user, and also for checking later on if the CRC is verified
        while(F1==0){
            F1=XORFunC(InputB, PolyInput, (HSL*4));
        }
        //Prints the CRC in Binary and HEX to user
        printf("\nThe CRC computed from the input: ");
        for(z=0; z<3; z++){
            printf("%c%c%c%c ", InputHT[(HSL*4)-12+(z*4)+0], InputHT[(HSL*4)-12+(z*4)+1], InputHT[(HSL*4)-12+(z*4)+2], InputHT[(HSL*4)-12+(z*4)+3]);
        } printf("(bin) = ");
        for(z=0; z<3; z++){
            temp=ConvertBtoH(InputHT[(HSL*4)-12+(z*4)+0], InputHT[(HSL*4)-12+(z*4)+1], InputHT[(HSL*4)-12+(z*4)+2], InputHT[(HSL*4)-12+(z*4)+3]);
            printf("%c", temp);
        } printf(" (hex)\n\nDid the CRC check pass? (Yes or No): ");
        //Checks through the final array calculated from XORFunC looking for any 1s...
        for(z=0; z<(HSL*4); z++){
            //...if there are any 1s in the final line, then the given CRC was not the actual CRC which allows this to throw a flag value indicating as such
            if(InputB[z]=='1'){
                CheckA=1;
            }
        }
        if(CheckA==1){
            printf("No\n");
        }else{
            printf("Yes\n");
        }
    }
    return (1);
}
//Prints the header of the program to the user
void HeaderPrint(){
    int a;
    for(a=0; a<62; a++){
        printf("-");
    }
    printf("\n\nCIS3360 Fall 2017 Integrity Checking Using CRC\nAuthor: Brian Wittel\n\n");
    return;
}
//XOR used mainly in calculation, but also used in verification
int XORFunC(char InputB[], char PolyInput[], int BSL){
    int a=0, b=0, c, UXL=(BSL-12);
    while(a<UXL){
        if(InputB[a]=='1'){
            break;
        }
        a++;
    }
    while(b<13 && a<UXL){
        if(InputB[a+b]==PolyInput[b]){
            InputB[a+b]='0';
        }else{
            InputB[a+b]='1';
        }
        b++;
    }
    if(a>=UXL){
        return(1);
    }else{
        for(c=0; c<BSL/4; c++){
            printf("%c%c%c%c ", InputB[(c*4)+0], InputB[(c*4)+1], InputB[(c*4)+2], InputB[(c*4)+3]);
        }printf("\n");
        return(0);
    }
}
//XOR used in the verification portion (similar to calculation sans printf)
int XORFunV(char InputHT[], char PolyInput[], int BSL){
    int a=0, b=0, c, UXL=(BSL-12);
    while(a<UXL){
        if(InputHT[a]=='1'){
            break;
        }
        a++;
    }
    while(b<13 && a<UXL){
        if(InputHT[a+b]==PolyInput[b]){
            InputHT[a+b]='0';
        }else{
            InputHT[a+b]='1';
        }
        b++;
    }
    if(a>=UXL){
        return(1);
    }else{
        return(0);
    }
}
//Converts from Binary to HEX while returning the HEX character
char ConvertBtoH(char A, char B, char C, char D){
    if(A=='1'){
        if(B=='1'){
            if(C=='1'){
                if(D=='1'){
                    return 'F';
                }else{
                    return 'E';
                }
            }else{
                if(D=='1'){
                    return 'D';
                }else{
                    return 'C';
                }
            }
        }else{
            if(C=='1'){
                if(D=='1'){
                    return 'B';
                }else{
                    return 'A';
                }
            }else{
                if(D=='1'){
                    return '9';
                }else{
                    return '8';
                }
            }
        }
    }else{
        if(B=='1'){
            if(C=='1'){
                if(D=='1'){
                    return '7';
                }else{
                    return '6';
                }
            }else{
                if(D=='1'){
                    return '5';
                }else{
                    return '4';
                }
            }
        }else{
            if(C=='1'){
                if(D=='1'){
                    return '3';
                }else{
                    return '2';
                }
            }else{
                if(D=='1'){
                    return '1';
                }else{
                    return '0';
                }
            }
        }
    }
}
//Converts from HEX to Binary
void ConvertHtoB(char A, char TempH[]){
    switch(A){
        case '0':
            TempH[0]='0';
            TempH[1]='0';
            TempH[2]='0';
            TempH[3]='0';
            break;
        case '1':
            TempH[0]='0';
            TempH[1]='0';
            TempH[2]='0';
            TempH[3]='1';
            break;
        case '2':
            TempH[0]='0';
            TempH[1]='0';
            TempH[2]='1';
            TempH[3]='0';
            break;
        case '3':
            TempH[0]='0';
            TempH[1]='0';
            TempH[2]='1';
            TempH[3]='1';
            break;
        case '4':
            TempH[0]='0';
            TempH[1]='1';
            TempH[2]='0';
            TempH[3]='0';
            break;
        case '5':
            TempH[0]='0';
            TempH[1]='1';
            TempH[2]='0';
            TempH[3]='1';
            break;
        case '6':
            TempH[0]='0';
            TempH[1]='1';
            TempH[2]='1';
            TempH[3]='0';
            break;
        case '7':
            TempH[0]='0';
            TempH[1]='1';
            TempH[2]='1';
            TempH[3]='1';
            break;
        case '8':
            TempH[0]='1';
            TempH[1]='0';
            TempH[2]='0';
            TempH[3]='0';
            break;
        case '9':
            TempH[0]='1';
            TempH[1]='0';
            TempH[2]='0';
            TempH[3]='1';
            break;
        case 'A':
            TempH[0]='1';
            TempH[1]='0';
            TempH[2]='1';
            TempH[3]='0';
            break;
        case 'B':
            TempH[0]='1';
            TempH[1]='0';
            TempH[2]='1';
            TempH[3]='1';
            break;
        case 'C':
            TempH[0]='1';
            TempH[1]='1';
            TempH[2]='0';
            TempH[3]='0';
            break;
        case 'D':
            TempH[0]='1';
            TempH[1]='1';
            TempH[2]='0';
            TempH[3]='1';
            break;
        case 'E':
            TempH[0]='1';
            TempH[1]='1';
            TempH[2]='1';
            TempH[3]='0';
            break;
        case 'F':
            TempH[0]='1';
            TempH[1]='1';
            TempH[2]='1';
            TempH[3]='1';
            break;
        default:
            printf("---WARNING! ERROR IN HEX TO BINARY!---");
    }
    return;
}
