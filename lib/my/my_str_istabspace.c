/*
** EPITECH PROJECT, 2019
** my_str_istabspace
** File description:
** found if str is only space/tab
*/

#include "my.h"

int my_str_istabspace(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] < '\t' || str[i] > '\t')
        && (str[i] < ' ' || str[i] > ' '))
            return (0);
    }
    return (1);
}
