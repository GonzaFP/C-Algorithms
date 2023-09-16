#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double new_colour = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/ 3.0;
            image[i][j].rgbtRed = round(new_colour);
            image[i][j].rgbtGreen = round(new_colour);
            image[i][j].rgbtBlue = round(new_colour);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int midpoint = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < midpoint; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempArray[height][width];
    int Gx[] = {-1,0,1,-2,0,2,-1,0,1};
    int Gy[] = {-1,-2,-1,0,0,0,1,2,1};
    // makng a copy of image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempArray[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int newRed = 0, newGreen = 0, newBlue = 0;
            int GxRed = 0, GyRed = 0, GxGreen = 0, GyGreen = 0, GxBlue = 0, GyBlue = 0;
            int GxCount = 0;
            int GyCount = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int a = -1; a < 2; a++)
                {
                    if ((i + k) < 0 || (i + k) > height - 1 || (j + a) < 0 || (j + a) > width - 1)
                    {
                        GxRed += 0;
                        GyRed+= 0;

                        GxGreen += 0;
                        GyGreen += 0;

                        GxBlue += 0;
                        GyBlue += 0;
                        GxCount++;
                        GyCount++;
                    }
                   else
                   {
                     GxRed += tempArray[i + k][j + a].rgbtRed * Gx[GxCount];
                    GxGreen += tempArray[i + k][j + a].rgbtGreen * Gx[GxCount];
                    GxBlue += tempArray[i + k][j + a].rgbtBlue * Gx[GxCount];

                    GyRed += tempArray[i + k][j + a].rgbtRed * Gy[GyCount];
                    GyGreen += tempArray[i + k][j + a].rgbtGreen * Gy[GyCount];
                    GyBlue += tempArray[i + k][j + a].rgbtBlue * Gy[GyCount];
                    GxCount++;
                    GyCount++;
                   }
                }
            }

            newRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            newGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));
            newBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));

            image[i][j].rgbtRed = newRed > 255 ? 255 : newRed;
            image[i][j].rgbtGreen = newGreen > 255 ? 255 : newGreen;
            image[i][j].rgbtBlue = newBlue > 255 ? 255 : newBlue;
    }
    }
    return;
}
