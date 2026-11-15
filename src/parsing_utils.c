#include "codexion.h"


int char_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int is_valid_digit_string(const char *str)
{
    int i;

    if (str == NULL || str[0] == '\0')
        return (0);
    i = 0;
    while (str[i] != '\0')
    {
        if (!char_is_digit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int long_string(const char *str, long *out)
{
    long result;
    int i;

    result = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (result > (LONG_MAX - (str[i] - '0')) / 10)
            return (0);
        result = result * 10 + (str[i] - '0');
        i++;
    }
    *out=result;
    return (1);
}

int parse_numeric_field(const char *str, long *out)
{
    if (!is_valid_digit_string(str))
        return (0);
    if (!long_string(str, out))
        return (0);
    return(1);
}

