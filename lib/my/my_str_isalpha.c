/*
** EPITECH PROJECT, 2018
** my_str_isalpha
** File description:
** my_str_isalpha
*/

#include "my.h"

int my_str_isalpha(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
            return (0);
    }
    return (1);
}
