/*
** EPITECH PROJECT, 2018
** task03
** File description:
** reverse a string
*/

#include "my.h"

char *my_revstr(char *str)
{
    char temp;
    int str_len = 0;

    str_len = my_strlen(str);
    for (int i = 0; i < str_len / 2; ++i){
        temp = str[i];
        str[i] = str[str_len - 1 - i];
        str[str_len - 1 - i] = temp;
    }
    return (str);
}
