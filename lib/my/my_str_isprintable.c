/*
** EPITECH PROJECT, 2018
** my_str_isprintable
** File description:
** my_str_isprintable
*/

#include "my.h"

int my_str_isprintable(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < ' ' || str[i] > '~')
            return (0);
    }
    return (1);
}
