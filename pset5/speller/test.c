#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

int main(void)
{
    bool loaded = load("dictionaries/small");

    if (loaded)
    {
        printf("Hello, World!\n");
    }
    else
    {
        printf("Hello, World!1\n");
    }

    return 0;
}