#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the user name
    string name = get_string("What's your name? ");

    //Say hello to the user
    printf("hello, %s\n", name);
}