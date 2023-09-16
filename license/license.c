/**
 * ! Suppose you work for a company that develops AI-enhanced license plate recognition technology. As you develop your technology, you may want to use actual license plate numbers as test data. You have a text file with some plate numbers you want to analyze, so you first try reading from that text file and printing out the license plates, to test your file-reading logic. But when you run your program, only the last number prints 8 times! What went wrong?
 * ! answer on line 22 and 37
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    /*
        ! The original code was char *plates[8] which is a pointer to a 2D array of 8 elements but the author tries to copy the license plates using code on line 39 i.e plates[idx] = buffer. This clears that array on each iteration since the array can only point to one array at a time. 
        ! I changed the code to char plates[8][7] which is an array of 8 array with 7 elements each and then, during each iteration, I copied a string to the array at position idx.
    */ 
    char plates[8][7];
    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        return 1;
    }
    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // plates[idx] = buffer;
        // Save plate number in array
        strcpy(plates[idx],buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }
    fclose(infile);
}
