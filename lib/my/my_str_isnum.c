/*
** EPITECH PROJECT, 2018
** my_str_isnum
** File description:
** my_str_isnum
*/

#include "my.h"

int my_str_isnum(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}
