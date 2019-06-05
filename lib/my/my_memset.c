/*
** EPITECH PROJECT, 2018
** my_memset
** File description:
** my_memset
*/

#include "my.h"

void *my_memset(void *ptr, int c, size_t n)
{
    char *tmp = (char *)ptr;

    while (n--) {
        *tmp++ = c;
    }
    return (ptr);
}