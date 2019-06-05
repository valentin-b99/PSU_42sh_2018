/*
** EPITECH PROJECT, 2018
** my_showstr
** File description:
** my_showstr
*/

#include "my.h"

int my_showstr_octal(char *str)
{
    int size = 0;

    if (*str == '\0')
        return (0);
    if (*str != '\0' && *str >= ' ' && *str <= '~')
        size += my_putchar(str[0]);
    if ((*str != '\0' && *str < ' ') || *str > '~') {
        size += my_putchar('\\');
        if (*str < 64)
            size += my_putchar('0');
        if (*str < 8)
            size += my_putchar('0');
        size += my_putnbr_base(*str, "01234567", 0);
    }
    size += my_showstr_octal(str + 1);
    return (size);
}