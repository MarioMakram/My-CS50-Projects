#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int h = get_int("What is the height: ");
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < h - i - 1; j++)
        {
            printf(" ");
        }
        for(int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for(int m = 0; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");

    }
}
