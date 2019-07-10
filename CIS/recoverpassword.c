/*
 * University of Central Florida
 * CIS 3360 - Fall 2017
 * Author: Brian Wittel
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){

    //printf("%s %s", argv[2], argv[1]);
    int i, F1=0, j=0, HoldVal, k=0, kHold=0, F2=0, LeftHash, RightHash, z, HashTest;
    char temp[8], tempASCII[12], tempHolding[1000][6], LHolding[4], RHolding[8];
    int Testing=atoi(argv[2]), LeftTest, RightTest;
    FILE *DFN;
    DFN=fopen(argv[1], "r");

    for(i=0;i<40;i++){
        printf("-");
    }printf("\n\nCIS3360 Password Recovery by Brian Wittel\n\n   Dictionary file name       : %s\n   Salted password hash value : %s\n\nIndex   Word   Unsalted ASCII equivalent\n\n", argv[1], argv[2]);
    while(F1==0){

        if(fgets(temp, 8, (FILE*)DFN)==NULL){
            F1=1;
        }
        for(i=0;i<6;i++){
            tempHolding[j][i]=temp[i];
        }
        j++;
    }
    while(j>1){
        printf("%4d :  ", k+1);
        for(i=0;i<6;i++){
            printf("%c", tempHolding[k][i]);
        }printf(" ");
        for(i=0;i<6;i++){
            HoldVal=tempHolding[k][i];
            tempASCII[(i*2)]=HoldVal/10;
            tempASCII[(i*2)+1]=HoldVal%10;
            printf("%d%d", tempASCII[(i*2)], tempASCII[(i*2)+1]);
        }printf("\n");
        for(i=0;i<999;i++){
            for(z=0;z<12;z++){
                if(z<5){
                    LHolding[z]=tempASCII[z];
                }else{
                    RHolding[z]=tempASCII[z];
                }
            }
            LeftTest=atoi(LHolding);
            RightTest=atoi(RHolding);
            LeftHash=(i*10000)+LeftTest;
            RightHash=RightTest;
            HashTest=((243*LeftHash)+RightHash)%85767489;
            if(HashTest==Testing){
                //F2=1;
            }
        }
        j--, k++;
    }
    if(F2==1){
        printf("\nPassword recovered:\n   Password            : %d\n   ASCII value         : %d\n   Salt value          : %d\n   Combinations tested : %d\n", 1, 1, 1, kHold);
    }else{
        printf("\nPassword not found in dictionary\n\nCombinations tested: %d\n", k*1000);
    }
    return (0);
}
