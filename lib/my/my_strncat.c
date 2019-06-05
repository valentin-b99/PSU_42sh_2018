/*
** EPITECH PROJECT, 2018
** task03
** File description:
** same as strcat but with n as limit
*/

#include "my.h"

char *my_strncat(char *dest, char *src, int n)
{
    int dest_len = my_strlen(dest);
    int i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return (dest);
}