#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 100;
    while (n > 23 || n < 1)
    {
        if (n == 0)
            return 0;
        n = get_int("Height: ");
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w < n - i; w++)
            printf(" ");

        for (int h = 0; h < i * 2; h++)
        {
            if (h == i)
                printf("  ");
            printf("#");
        }

        printf("\n");
    }
}