#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompting for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //This for loop is the height of the pyramid
    for (int i = height - 1; i >= 0; i--)
    {
        //This for loop is to right-align the left pyramid
        for (int j = 0; j < i; j++)
        {
            printf(" ");
        }

        //This for loop is to draw the hashes of the left pyramid
        for (int k = height; k > i; k--)
        {
            printf("#");
        }

        //This is the gap between the pyramid
        printf("  ");

        //This for loop is to draw the hashes of the right pyramid
        for (int m = height; m > i; m--)
        {
            printf("#");
        }

        printf("\n");
    }
}