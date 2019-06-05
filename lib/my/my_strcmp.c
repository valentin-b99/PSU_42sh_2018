/*
** EPITECH PROJECT, 2018
** task05
** File description:
** return < 0 if str1 < str2, = 0 if str1 = str2
** > 0 if str1 > str2
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    for (; *s1 == *s2; ++s1, ++s2)
        if (*s1 == '\0')
            return (0);
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : 1);
}