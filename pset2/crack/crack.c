#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>

#define _XOPEN_SOURCE

char letter(int i)
{
    if (i == 52)
    {
        return ' ';
    }
    else if (i < 26)
    {
        return i + 65;
    }
    else
    {
        return i + 97;
    }
}

int main(int argc, char *argv[])
{
    char *hash;
    char *salt;
    char *guess_hash;
    char *key;

    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    hash = argv[1];
    guess_hash = malloc(sizeof(char) * 14);
    salt = malloc(sizeof(char) * 3);
    key = malloc(sizeof(char) * 5);

    salt = strncat(salt, hash, 2);

    for (int a = 0; a < 52; a++)
    {
        key[0] = letter(a);
        for (int b = 0; b <= 52; b++)
        {
            key[1] = letter(b);
            for (int c = 0; c <= 52; c++)
            {
                key[2] = letter(c);
                for (int d = 0; d <= 52; d++)
                {
                    key[3] = letter(d);
                    guess_hash = crypt(key, salt);
                    if (strcmp(guess_hash, hash) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}