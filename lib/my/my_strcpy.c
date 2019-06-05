/*
** EPITECH PROJECT, 2018
** task01
** File description:
** copy a string into another
*/

#include "my.h"

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return (dest);
}
