#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize, endSize;
    int years = 0;

    do
    {
        startSize = get_int("Starting population size: ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    do
    {
        endSize = get_int("Ending population size: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    while (startSize < endSize)
    {
        startSize += (startSize / 3) - (startSize / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);

}
