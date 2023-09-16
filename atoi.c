//! this program converts a string to a number using recursion

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // Start with the last char and convert it into an integer value. Then shorten the string, removing the last char, and then recursively call convert using the shortened string as input, where the next char will be processed.

    int length = strlen(input);
    int number = 0;
    if (length == 1)
    {
        return number = (number * 10) + (input[0] - '0');
    }

    int last_number = input[length - 1] - '0';
    input[length - 1] = '\0';
    return number = (convert(input) * 10) + last_number;
}