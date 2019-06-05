/*
** EPITECH PROJECT, 2018
** task08
** File description:
** puts every letters in lowercase
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ' && str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
    return (str);
}
