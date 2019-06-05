/*
** EPITECH PROJECT, 2018
** my_realloc
** File description:
** my_realloc
*/

#include "my.h"

char *my_realloc(char *ptr, size_t size)
{
    char *ptr_realloc = x_memset(0, size + 1, sizeof(char));
    int i = -1;

    if (ptr == NULL || ptr_realloc == NULL || size < 1)
        return (NULL);
    while (ptr[++i])
        ptr_realloc[i] = ptr[i];
    free(ptr);
    return (ptr_realloc);
}