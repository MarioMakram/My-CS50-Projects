#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
        (height = get_int("Please enter the height of the pyramids: "));
    while (height < 1);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int m = 0; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}
