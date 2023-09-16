// this program recovers deleted images from a memory card.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in each block
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // open memory card file
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open card file.
    FILE *memorycard = fopen(argv[1], "r");
    if (memorycard == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // buffer to store data
    uint8_t buffer[BLOCK_SIZE];
    int count = 0;
    char filename[8];
    FILE *imageptr;

    while (fread(buffer, 1, BLOCK_SIZE, memorycard) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0Xd8 && buffer[2] == 0Xff && (buffer[3] & 0Xf0) == 0Xe0)
        {
            //  first JPEG to be found.
            if (count == 0)
            {
                // creating a filename
                sprintf(filename, "%03i.jpg", count);
                // opening the file so as to write into it data stored in buffer.
                imageptr = fopen(filename, "w");

                if (imageptr == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(buffer, 1, BLOCK_SIZE, imageptr);
                count++;
            }
            else
            {
                // close old file that I have been writing to and then create a new one.
                fclose(imageptr);
                // creating a filename
                sprintf(filename, "%03i.jpg", count);

                // opening the file so as to write into it data stored in buffer.
                imageptr = fopen(filename, "w");
                if (imageptr == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(buffer, 1, BLOCK_SIZE, imageptr);
                count++;
            }
        }
        else
        {
            // continue writing to the old file.
            if (count > 0)
            {
                fwrite(buffer, 1, BLOCK_SIZE, imageptr);
            }
        }
    }
    fclose(imageptr);
    fclose(memorycard);
}