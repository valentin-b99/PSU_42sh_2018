/*
** EPITECH PROJECT, 2018
** my_puterr
** File description:
** my_puterr
*/

#include "my.h"

void my_puterr(char *str, int err_code)
{
    int len = my_strlen(str);

    write(2, str, len);
    exit(err_code);
}