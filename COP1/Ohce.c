// Name---: Brian Wittel
// NID----: br933378
// Project: Ohce
// Class--: COP 3502C
// Date---: 2018/01/24

#include <stdio.h>
#include "Ohce.h"

double difficultyRating(void) {
    return 2.0;
}

double hoursSpent(void) {
    return 4.5;
}

int main(int argc, char **argv) {
    int i, j, k, F1=0, F2=0;
    //Main Loop of Ohce. Starts from 1, the first argument given after the program name, up until the final given argument
    for (i=1; i<argc; i++) {
        //Resets Flag1 to 0 with each iteration (More on this later)
        F1=0;
        //Secondary loop of Ohce. This navigates the current (i) argument with two purposes
        for (j=0; j>=0; j++) {
            //First purpose is to initially search for the letter 'e' or 'E'
            if (argv[i][j]=='E' || argv[i][j]=='e') {
                //If 'e' or 'E' is found Flag1 is set to 1 allowing...
                F1=1;
            } else if ((argv[i][j]=='C' || argv[i][j]=='c') && F1==1) {
                //...the conditions to check for 'C' or 'c' on the next loop and so on and so forth
                F1=2;
            } else if ((argv[i][j]=='H' || argv[i][j]=='h') && F1==2) {
                F1=3;
            } else if ((argv[i][j]=='O' || argv[i][j]=='o') && F1==3) {
                //If Ohce does find the word 'echo' in any sort of capitalization Flag2 is set to the value of 1 for later
                F2=1;
            } else {
                //If no matching letter is found we reset Flag1 to zero and start again (Unless the next letter is an 'E' or 'e' in which case Flag1 is just set again to 1)
                F1=0;
            }
            //This loop continues until an end character is reached...
            if(argv[i][j]== '\0'){
                //Once reached we set the value k to the arguments length, and break from the Secondary Loop (Which would otherwise be infinite)
                k=j;
                break;
            }
        }
        //This loop receives the length of the given argument, and working backwards prints each character to the user
        for (k; k>=0; k--) {
            //This checks for if we are at the start of the word where the space is not needed and as such not printed
            if (argv[i][k]!=0)
                printf("%c", argv[i][k]);
        }
        //This applies the spaces between words as long as it is not the last word
        if ((i+1)<argc)
            printf(" ");
    }
    //As long as Ohce is given an argument, more so than just the programs name, we print a new line at the end of the output
    if (argc>1)
        printf("\n");
    //From The Secondary Loop if Flag2 was triggered and set to 1, meaning the word 'echo' in some form of capitalization was present in a given argument, a message is printed out to the user
    if (F2==1)
        printf("Echo, echo, echo!\n");
    return 0;
}
