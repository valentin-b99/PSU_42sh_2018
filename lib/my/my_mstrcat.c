/*
** EPITECH PROJECT, 2018
** my_strcat
** File description:
** my_strcat
*/

#include "my.h"

char *my_mstrcat(char *str1, char *str2)
{
    int str1_len = str1 == NULL ? 0 : my_strlen(str1);
    char *result;

    if ((result = malloc(sizeof(char) *
        (str1_len + my_strlen(str2) + 1))) == NULL)
        return (NULL);
    my_memset(result, 0, str1_len + my_strlen(str2) + 1);
    for (int i = 0; str1 && str1[i]; i++)
        result[i] = str1[i];
    for (int i = 0; str2[i]; i++)
        result[str1_len + i] = str2[i];
    return (result);
}