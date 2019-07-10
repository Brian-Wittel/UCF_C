// Name-: Brian Wittel
// NID--: br933378
// Date-: 2018 / 06 / 10
// Class: COP 3503C
// Assignment: Sneaky Knights (#3)

import java.awt.Point;
import java.util.*;

public class SneakyKnights {
    
    // HashSet to contain all given knights
    private static HashSet<Point> currKnights;
    
    // Returns row of given coordinate string (Written by Wittel in SneakyQueens)
    public static int rowReturn(String holding, int length, int currCord) {
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
    
    // Returns column of given coordinate string (Written by Wittel in SneakyQueens)
    public static int columnReturn(String holding, int length, int currCord) {
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

    // Returns an int which represents the amount of alpha characters in the given coordinate system as well as the starting location for the number coordinates in given string (Written by Wittel in SneakyQueens)
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
    
    // Checks to see if any of the given knights can attack each other on a given board size
    public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize) {
        // Critical Variables: HashSet, Point for attack test, 2d Array of valid moves for knight
        currKnights = new HashSet<>(); 
        Point currAttack = new Point();
        int i, midBreak;
        String holding;
        int[][] attackMoves = {{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{-1,2},{1,2}};
        
        // Main loop dictated by amount of knights given
        for(i=0;i<coordinateStrings.size();i++) {
            // Each iteration holds the current working coordinate as well as creates a new knightCoord Point variable to insert into HashSet
            holding = coordinateStrings.get(i);
            Point knightCoord = new Point();
            // From given coordinate find the point at which alpha turns to numeric
            midBreak = cordReturn(holding, holding.length());
            // Error check for cordReturn
            if(midBreak == -1) {
                System.out.println("---ERROR! (cordReturn -1)---");
                return false;
            }   
            // Using previously written functions find the x and y positions of the knight on the board before adding to the HashSet
            knightCoord.y =  rowReturn(holding, holding.length(), midBreak);
            knightCoord.x =  columnReturn(holding, holding.length(), midBreak);
            currKnights.add(knightCoord);
            // Going through each attack move...
            for(int j[] : attackMoves) {
                // ...find where each attack will land...
                currAttack.x = knightCoord.x + j[0];
                currAttack.y = knightCoord.y + j[1];
                // ...before checking if said attack is a valid move on the board. If so...
                if(currAttack.x > 0 && currAttack.y > 0 && currAttack.x <= boardSize && currAttack.y <= boardSize) {
                    // ...check to see if a knight is already present. If so...
                    if(currKnights.contains(currAttack)) {
                        // ...return false as this is an attack!
                        return false;
                    }
                } 
            }
        }
        // If false is never returned, and we reach the end of the given coordinate strings, then all the knights are safe!
        return true;
    }
    
    // Difficulty rating of 1 - 5
    public static double difficultyRating() {
        return 3.5;
    }
    
    // Hours spent on this program
    public static double hoursSpent() {
        return 10.0;
    }
    
}
