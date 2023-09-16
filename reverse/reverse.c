/*
    Reverses an audio file by reading it backwards.
*/

#include "wav.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;
int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // User must provide 2 files when they run the program.
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *inputaudio = fopen(argv[1], "r");
    if (inputaudio == NULL)
    {
        printf("File could not be opened\n");
        return 1;
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, inputaudio);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *outputaudio = fopen(argv[2], "w");
    if (outputaudio == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, HEADER_SIZE, 1, outputaudio);
    // Use get_block_size to calculate size of block
    // TODO #7
    int BLOCKSIZE = get_block_size(header);
    BYTE buffer[BLOCKSIZE];
    fread(buffer, BLOCKSIZE, 1, inputaudio);
    // Write reversed audio to file
    // TODO #8

    // get the current position after reading the header
    int position1 = ftell(inputaudio);

    // Move pointer to the end of the file.
    fseek(inputaudio, 0, SEEK_END);

    // get the position
    int position2 = ftell(inputaudio);
    int length = (position2 - HEADER_SIZE) / BLOCKSIZE;

    // move backwards 1 blocksize
    fseek(inputaudio, -1 * BLOCKSIZE, SEEK_CUR);

    while (length > 0)
    {
        fread(buffer, BLOCKSIZE, 1, inputaudio);
        fwrite(buffer, BLOCKSIZE, 1, outputaudio);
        fseek(inputaudio, -2 * BLOCKSIZE, SEEK_CUR);
        length--;
    }
    fclose(inputaudio);
    fclose(outputaudio);
}

int check_format(WAVHEADER header)
{
    BYTE format[] = "WAVE";
    // TODO #4
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] == format[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int BLOCKSIZE;
    BLOCKSIZE = (header.numChannels * (header.bitsPerSample / 8));
    return BLOCKSIZE;
}