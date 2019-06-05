/*
** EPITECH PROJECT, 2018
** my_str_islower
** File description:
** my_str_islower
*/

#include "my.h"

int my_str_islower(char *str)
{
    if (my_str_isalpha(str) == 0)
        return (0);
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            return (0);
    }
    return (1);
}
