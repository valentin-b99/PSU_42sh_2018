/*
** EPITECH PROJECT, 2018
** task04
** File description:
** return a pointer to the first occurence
** to the string given as parameter
*/

#include "my.h"

int my_strstr_intermediate(char *a, char *b)
{
    while (1) {
        if (*b == 0)
            return (0);
        if (*a++ != *b++)
            return (84);
    }
}

char *my_strstr(char *string, char *substring)
{
    char *a = NULL;
    char *b = NULL;

    b = substring;
    if (*b == 0)
        return (string);
    for (; *string != 0; ++string) {
        if (*string != *b)
            continue;
        a = string;
        if (my_strstr_intermediate(a, b) == 0)
            return (string);
        b = substring;
    }
    return (NULL);
}
