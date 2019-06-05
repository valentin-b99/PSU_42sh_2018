/*
** EPITECH PROJECT, 2019
** my_strnncat.c
** File description:
** my_strnncat
*/

#include "my.h"

char *my_strnncat(int start, int end, char *str, char *add_str)
{
    char *result;

    if ((result = malloc(sizeof(char) * (start + my_strlen(add_str) +
        (my_strlen(str)) + 1))) == NULL)
        return (NULL);
    my_memset(result, 0, start + my_strlen(add_str) +
    (my_strlen(str)) + 1);
    result = my_strncat(result, str, start);
    result = my_strcat(result, add_str);
    result = my_strcat(result, str + end);
    return (result);
}