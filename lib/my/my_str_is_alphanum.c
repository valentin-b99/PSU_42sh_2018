/*
** EPITECH PROJECT, 2019
** my_str_is_alphanum
** File description:
** my_str_is_alphanum
*/

#include "./my.h"

int my_str_is_alphanum(char *str)
{
    int i = -1;

    while (str[++i]) {
        if ((str[i] < '0' || str[i] > '9') && (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < 'a' || str[i] > 'z'))
            return (0);
    }
    return (1);
}