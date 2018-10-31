#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *encrypt(char *, char *);
bool islower(int);
bool isupper(int);
bool isalpha(int);
int len(const char *);
bool validate(char *);

int MESSAGE_MAX_LENGTH = 40;

int main(int argc, char *argv[])
{
    if (argc == 2 && validate(argv[1]))
    {
        char *keyword = argv[1];

        // user's message input
        char message[MESSAGE_MAX_LENGTH];
        printf("plaintext: ");
        fgets(message, MESSAGE_MAX_LENGTH, stdin);

        // encrypting inserted message
        char *encrypted_message = encrypt(message, keyword);

        printf("ciphertext: %s", encrypted_message);
    }
    else
    {
        printf("Make sure your program has two arguments. Please, try again.\n");
        return 1;
    }
}

char *encrypt(char *s, char *keyword)
{
    char *e = malloc(MESSAGE_MAX_LENGTH * sizeof(char)); // encrypted text
    int j = 0;
    int keyword_length = len(keyword);

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isupper(s[i]) && isupper(keyword[j]))
        {
            e[i] = (s[i] - 13 + (keyword[j] - 13) % 26) % 26 + 65;
            j = (j + 1) % keyword_length;
        }
        else if (isupper(s[i]) && islower(keyword[j]))
        {
            e[i] = (s[i] - 13 + (keyword[j] - 19) % 26) % 26 + 65;
            j = (j + 1) % keyword_length;
        }

        else if (islower(s[i]) && isupper(keyword[j]))
        {
            e[i] = (s[i] - 19 + (keyword[j] - 13) % 26) % 26 + 97;
            j = (j + 1) % keyword_length;
        }
        else if (islower(s[i]) && islower(keyword[j]))
        {
            e[i] = (s[i] - 19 + (keyword[j] - 19) % 26) % 26 + 97;
            j = (j + 1) % keyword_length;
        }
        else
        {
            e[i] = s[i];
        }
    }

    return e;
}

bool validate(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isalpha(s[i])) {
            return false;
        }
    }

    return true;
}

bool isalpha(int n)
{
    if (!islower(n) && !isupper(n)) {
        return false;
    }

    return true;
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

int len(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}
