// Name-: Brian Wittel
// NID--: br933378
// Date-: 2018 / 05 / 28
// Class: COP 3503C
// Assignment: Sneaky Queens (#1)

import java.util.ArrayList;

public class SneakyQueens {
    
    public static int rowReturn(String holding, int currCord, int length) {
        int sum = 0, current;
        // Loop to work through second half of given coordinates
        for(int i = 0;i<length-currCord;i++) {
            // Takes the current character, adjusts the value for number ASCII, and sets as an int
            current = (int) holding.charAt(currCord + i) - 48;
            // Adds the current int to sum in the correct position (left to right)
            sum += (current * Math.pow(10, (length-currCord)-i-1));
        }
        return sum;
    }
    
    public static int columnReturn(String holding, int currCord, int length) {
        int sum = 0, current;
        // Loop to work through first half of given coordinates
        for(int i = 0;i<currCord;i++) {
            // Takes the current character, adjusts the value for alpha ASCII, and sets as an int
            current = (int) holding.charAt(i) - 96;
            // Adds the current int to sum after adjusting for its value in base twenty six
            sum += (current * Math.pow(26, (currCord-i-1)));
        }
        return sum;
    }
    
    public static int leftDiagReturn(int currRow, int currCol) {
        // With the smallest bottom-left sqaure being the first diagonal this evaluates the left diagonal the Queen sits on
        return (currRow-1)+currCol;
    }
    
    public static int rightDiagReturn(int currRow, int currCol, int boardSize) {
        // With the smallest bottom-right square being the first diagonal this evaluates the right diagonal the Queen sits on
        return (boardSize-currCol)+(currRow);
    }
    
    // Returns an int which represents the amount of alpha characters in the given coordinate system as well as the starting location for the number coordinates in given string
    public static int cordReturn(String holding, int length) {
        char current, next;
        // This helps to binary search through the given coordinates
        int middle = length/2, i;
        int space = middle/2;
        // Double check that our division does not result in a 0 (No changes and possible looping further down if 0)
        if(space == 0)
            space = 1;
        current = holding.charAt(middle-1);
        next = holding.charAt(middle);
        // Loop to work through binary search of given coordinates
        for(i=0;i<length;i++) {
            // If current is alpha
            if((int) current >= 97) {
                // If the following character is a number
                if((int) next <= 57) {
                    // We have found our point!
                    return middle;
                // If the following character is alpha
                } else {
                    middle += space;
                    space = space/2;
                    if(space == 0)
                        space = 1;
                    current = holding.charAt(middle-1);
                    next = holding.charAt(middle);
                }
            } 
            // If current is number
            else if((int) current <= 57) {
                middle -= space;
                space = space/2;
                if(space == 0)
                    space = 1;
                if(middle == 0) {
                    return 0;
                } else {
                    current = holding.charAt(middle-1);
                    next = holding.charAt(middle);
                }
            }
        }
        // If -1 is returned then error
        return -1;
    }
    
    
    public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize) {
        // Creates multiple 1D arrays that represent each individual characteristic the Queen can have
        int[] boardColumn = new int[boardSize];
        int[] boardRow = new int[boardSize];
        int[] boardLeftDiag = new int[(2*boardSize)-1];
        int[] boardRightDiag = new int[(2*boardSize)-1];
        
        int i, currCord, currRow, currCol, currLeftD, currRightD;
        String holding;
        // Loop based off of amount of coordinates
        for(i=0;i<coordinateStrings.size();i++) {
            // Place current working coordinate into a holding variable
            holding = coordinateStrings.get(i);
            // Find where the change from Column to Row coordinates are located
            currCord = cordReturn(holding, holding.length());
            // From this found location evaluate what the given Column and Row are...
            currCol = columnReturn(holding, currCord, holding.length());
            currRow = rowReturn(holding, currCord, holding.length());
            // ...And then utilize those values to determine which diagonals the Queen sits on
            currLeftD = leftDiagReturn(currRow, currCol);
            currRightD = rightDiagReturn(currRow, currCol, boardSize);
            // If the found Row, Column, Left Diagonal, or Right Diagonal are occupied...
            if(boardRow[currRow-1] != 0 || boardColumn[currCol-1] != 0 || boardLeftDiag[currLeftD-1] != 0 || boardRightDiag[currRightD-1] != 0) {
                // ...we have a collision! Otherwise...
                return false;
            } else {
                // ...add the current Queen to the list
                boardRow[currRow-1] = 1;
                boardColumn[currCol-1] = 1;
                boardLeftDiag[currLeftD-1] = 1;
                boardRightDiag[currRightD-1] = 1;
            }
        }
        // If all Queens are added, and no collisions are found, then the Queens are in fact safe!
        return true;
    }
    
    public static double difficultyRating() {
        return 1.5;
    }
    
    public static double hoursSpent() {
        return 3.0;
    }
    
}
