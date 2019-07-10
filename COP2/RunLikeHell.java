// Name-: Brian Wittel
// NID--: br933378
// Date-: 2018 / 07 / 31
// Class: COP 3503C
// Assignment: RunLikeHell (#7)

import java.util.*;
import java.io.*;

public class RunLikeHell {

    // By utilizing this call prior to the actual recursive call the necessary information, relating to the blocks provided, can be extrapolated
    public static int maxGainRecursiveStart(int[] blocks) {
        return maxGainRecursive(blocks, blocks.length-1, 0, 0);
    }

    // Actual recursive call. Utilizes the number of items present in the given block chain as well as the resulting value (this starts at 0)
    public static int maxGainRecursive(int[] blocks, int length, int item, int value) {
        // If we find ourselves out of the block array we do not alter any variables. If not though...
        if(item > length) {
            return 0;
        // ...and we are on the final item of the given chain we add the block to the value before returning said value. Otherwise...
        } else if(item == length) {
            return (value + blocks[item]);
        // ...perform no operation and proceed as normal.
        } else {
            ;
        }
        // Spawns two recursive calls where the item is taken in the first, and moved over to skip the next box, or left in the second
        return Math.max(maxGainRecursive(blocks, length, item+2, value+blocks[item]), maxGainRecursive(blocks, length, item+1, value));
    }

    public static int maxGain(int[] blocks) {
        int i;
        // If no array is passed return nothing along with...
        if(blocks == null) {
            return 0;
        // ...if an empty array is passed. In the case of...
        } else if(blocks.length == 0) {
            return 0;
        // ...a single block array being passed simply return the value of the lonely block. Otherwise...
        } else if(blocks.length == 1) {
            return blocks[0];
        // ...continue on as normal!
        } else {
            ;
        }
        // Array used to cache our dynamic solution (sized to n+1 hence no -1 on length)
        int memoCache[] = new int[blocks.length];
        // Creates the base cases, so to say, for the start of the cache. If we move through the cases above then the minimum length of the given block is 2.
        memoCache[0] = blocks[0];
        memoCache[1] = blocks[1];
        // To create an easier for loop below we check to see if the given length of the block is 3 or more. If so...
        if(memoCache.length >= 3) {
            // ...we assign the cache the value of the first entry as well as the third block. This value will always be higher than the initial value alone.
            memoCache[2] = memoCache[0] + blocks[2];
            // Here i is set to 3 which allow the program to chew through each next block. This happens by...
            for(i = 3;i < memoCache.length;i++) {
                // ...comparing the second to last box as well as the third to last box. Whichever is larger is added to the current block box value.
                memoCache[i] = Math.max(memoCache[i-3], memoCache[i-2]) + blocks[i];
                // NOTE: We do not look for four back as we could simply hit the box in between them increasing the value further.
            }
            // NOTE: Even if the loop above is not entered i is still set to 3. 
            // With the above in mind the last two slots of memoCache are compared for the larger value as these are the ends of the block chain and will hold the largest results
            return Math.max(memoCache[i-1], memoCache[i-2]);
        }
        // If the length of the given block chain is 2 then only the first two cases need to be compared
        return Math.max(memoCache[0], memoCache[1]);
    }

    public static double difficultyRating() {
        return 2.5;
    }

    public static double hoursSpent() {
        return 4.5;
    }
    
}