/*
** EPITECH PROJECT, 2018
** task02
** File description:
** display one-by-one the characters of a string
*/

#include "my.h"

int my_putstr(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i){
        my_putchar(str[i]);
    }
    return (0);
}
