#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *encrypt(char *, int);
bool islower(int);
bool isupper(int);

int MESSAGE_MAX_LENGTH = 20;

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // converting char* arg into int
        int key = atoi(argv[1]);

        // user's message input
        char message[MESSAGE_MAX_LENGTH];
        printf("plaintext: ");
        fgets(message, MESSAGE_MAX_LENGTH, stdin);

        // encrypting inserted message
        char *encrypted_message = encrypt(message, key);

        printf("ciphertext: %s", encrypted_message);
    }
    else
    {
        printf("Make sure your program has two arguments. Please, try again.\n");
        return 1;
    }
}

char *encrypt(char *s, int key)
{
    char *e = malloc(MESSAGE_MAX_LENGTH * sizeof(char)); // encrypted text
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isupper(s[i]))
        {
            e[i] = (s[i] - 13 + key) % 26 + 65;
        }
        else if (islower(s[i]))
        {
            e[i] = (s[i] - 19 + key) % 26 + 97;
        }
        else
        {
            e[i] = s[i];
        }
    }
    return e;
}

bool isupper(int n)
{
    if (n >= 65 && n <= 90)
    {
        return true;
    }

    return false;
}

bool islower(int n)
{
    if (n >= 97 && n <= 122)
    {
        return true;
    }

    return false;
}