/*
** EPITECH PROJECT, 2018
** task02
** File description:
** concatenates two strings
*/

#include "my.h"

char *my_strcat(char *dest, char *src)
{
    int dest_len = my_strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; ++i)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return (dest);
}
