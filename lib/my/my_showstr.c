/*
** EPITECH PROJECT, 2018
** my_showstr
** File description:
** my_showstr
*/

#include "my.h"

int my_showstr(char *str)
{
    if (*str == '\0')
        return (0);
    if (*str != '\0' && *str >= ' ' && *str <= '~')
        my_putchar(str[0]);
    if ((*str != '\0' && *str < ' ') || *str > '~') {
        my_putchar('\\');
        if (*str < 16)
            my_putchar('0');
        my_putnbr_base(*str, "0123456789abcdef", 0);
    }
    my_showstr(str + 1);
    return (0);
}