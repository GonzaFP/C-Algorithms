/*
    ! Apply different filters to an image such as black & white filter, sepia filter, blur, reflection"
*/ 
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double new_colour;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel, get the average of rgb and then set it as new colour.
            new_colour = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(new_colour);
            image[i][j].rgbtGreen = round(new_colour);
            image[i][j].rgbtRed = round(new_colour);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally. swap opposite pixels.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempArray;
    int midpoint = width / 2;
    for (int i = 0; i < height; i++)
    {
        // Swapping will be midpoint - 1 times.
        for (int j = 0; j < midpoint; j++)
        {
            tempArray = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tempArray;
        }
    }
    return;
}

// Blur image
void recur(int height, int width, RGBTRIPLE tempArray[height][width], int i, int j, int n, double Arr[])
{
    if (n == 0)
    {
        return;
    }
    n--;
     // pixels at the top do not have pixels before them.
    if (i - 1 < 0)
    {
        Arr[0] += (tempArray[i][j].rgbtRed + tempArray[i + 1][j].rgbtRed);
        Arr[1] += (tempArray[i][j].rgbtGreen + tempArray[i + 1][j].rgbtGreen);
        Arr[2] += (tempArray[i][j].rgbtBlue + tempArray[i + 1][j].rgbtBlue);
        Arr[3] += 2;
        recur(height, width, tempArray, i, j - 1, n, Arr);
    }
    // pixels at the bottom do not have pixels after them.
    else if (i + 1 > height - 1)
    {
        Arr[0] += (tempArray[i][j].rgbtRed + tempArray[i - 1][j].rgbtRed);
        Arr[1] += (tempArray[i][j].rgbtGreen + tempArray[i - 1][j].rgbtGreen);
        Arr[2] += (tempArray[i][j].rgbtBlue + tempArray[i - 1][j].rgbtBlue);
        Arr[3] += 2;

        recur(height, width, tempArray, i, j - 1, n, Arr);
    }
    else
    {
        Arr[0] += (tempArray[i][j].rgbtRed + tempArray[i + 1][j].rgbtRed + tempArray[i - 1][j].rgbtRed);
        Arr[1] += (tempArray[i][j].rgbtGreen + tempArray[i + 1][j].rgbtGreen + tempArray[i - 1][j].rgbtGreen);
        Arr[2] += (tempArray[i][j].rgbtBlue + tempArray[i + 1][j].rgbtBlue + tempArray[i - 1][j].rgbtBlue);
        Arr[3] += 3;
        recur(height, width, tempArray, i, j - 1, n, Arr);
    }
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempArray[height][width];
    double newRed = 0.0, newGreen = 0.0, newBlue = 0.0;
    // makng a copy of image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempArray[i][j] = image[i][j];
        }
    }

    // change rgb values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // array to store red, blue, green and counter values.
            double blurColours[] = {0.0, 0.0, 0.0, 0.0};
            // pixels on extreme left do not have pixels to their left.
            if (j == 0)
            {
                recur(height, width, tempArray, i, j + 1, 2, blurColours);
            }

             // pixels on extreme right do not have pixels to their right.
            else if (j == width - 1)
            {
                recur(height, width, tempArray, i, j, 2, blurColours);
            }
            else
            {
                recur(height, width, tempArray, i, j + 1, 3, blurColours);
            }
            newRed = blurColours[0] / blurColours[3];
            newGreen = blurColours[1] / blurColours[3];
            newBlue = blurColours[2] / blurColours[3];
            image[i][j].rgbtRed = round(newRed);
            image[i][j].rgbtGreen = round(newGreen);
            image[i][j].rgbtBlue = round(newBlue);
        }
    }
    return;
}
