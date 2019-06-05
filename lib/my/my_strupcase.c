/*
** EPITECH PROJECT, 2018
** task07
** File description:
** put every letter in uppercase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ' && str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
    }
    return (str);
}
