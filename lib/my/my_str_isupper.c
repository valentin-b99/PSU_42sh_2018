/*
** EPITECH PROJECT, 2018
** my_str_isupper
** File description:
** my_str_isupper
*/

#include "my.h"

int my_str_isupper(char *str)
{
    if (my_str_isalpha(str) == 0)
        return (0);
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z')
            return (0);
    }
    return (1);
}
