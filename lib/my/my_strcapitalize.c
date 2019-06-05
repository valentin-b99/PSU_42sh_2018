/*
** EPITECH PROJECT, 2018
** task09
** File description:
** capitalize first letter of each word
*/

#include "my.h"

char *my_strcapitalize(char *str)
{
    my_strlowcase(str);
    if (str[0] >= 'a' && str[0] <= 'z')
        str[0] = str[0] - 32;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] == ' ' || str[i] == '-' || str[i] == '+' || str[i] == ';')
            && (str[i + 1] >= 'a' && str[i + 1] <= 'z')) {
            str[i + 1] = str[i + 1] - 32;
        }
    }
    return (str);
}
