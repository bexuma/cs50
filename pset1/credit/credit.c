#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>

#define VISA1 13
#define VISA2 16
#define MASTERCARD 16
#define AMEX 15

int sum_from_second_last_digit(long long int);
int sum_from_last_digit(long long int);
bool double_digit(int);
bool single_digit(int);
void card_type(long long int);
bool is_valid_card(long long int);
int cc_number_length(long long int);

int main(void)
{
    long long int cc_number = get_long_long("Number: ");
    card_type(cc_number);
}

void card_type(long long int n)
{

    if (is_valid_card(n)
        && (cc_number_length(n) == VISA1 || cc_number_length(n) == VISA2)
        && (n / (long long int) pow(10, VISA1 - 1) == 4
            || n / (long long int) pow(10, VISA2 - 1) == 4))
    {
        printf("VISA\n");
    }
    else if (is_valid_card(n)
             && (cc_number_length(n) == MASTERCARD)
             && (n / (long long int) pow(10, MASTERCARD - 2) == 51
                 || n / (long long int) pow(10, MASTERCARD - 2) == 52
                 || n / (long long int) pow(10, MASTERCARD - 2) == 53
                 || n / (long long int) pow(10, MASTERCARD - 2) == 54
                 || n / (long long int) pow(10, MASTERCARD - 2) == 55
                ))
    {
        printf("MASTERCARD\n");
    }
    else if (is_valid_card(n)
             && (cc_number_length(n) == AMEX)
             && (n / (long long int) pow(10, AMEX - 2) == 34
                 || n / (long long int) pow(10, AMEX - 2) == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


int cc_number_length(long long int n)
{
    int count = 0;

    while (n > 0)
    {
        n = n / 10;
        count++;
    }

    return count;
}

bool is_valid_card(long long int n)
{
    if ((sum_from_second_last_digit(n) + sum_from_last_digit(n)) % 10 == 0)
    {
        return true;
    }

    return false;
}

int sum_from_second_last_digit(long long int n)
{
    // prep to access the second last digit
    n = n / 10;

    int value;
    int sum = 0;

    for (int i = 0; i < 14; i++)
    {
        // get the last digit of n, multiply by two
        value = (n % 10) * 2;

        if (double_digit(value))
        {
            sum += 1;
            sum += value % 10;
        }
        else if (single_digit(value))
        {
            sum += value;
        }

        // move 2 digits left
        n = n / 100;
    }

    return sum;
}

int sum_from_last_digit(long long int n)
{
    int sum = 0;

    for (int i = 0; i < 8; i++)
    {
        sum += n % 10;
        n /= 100;
    }

    return sum;
}

bool double_digit(int n)
{
    if (n / 10 == 1)
    {
        return true;
    }

    return false;
}

bool single_digit(int n)
{
    if (n / 10 == 0)
    {
        return true;
    }

    return false;
}