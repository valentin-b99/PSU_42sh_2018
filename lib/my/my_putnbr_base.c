/*
** EPITECH PROJECT, 2018
** my_putnbr_base
** File description:
** my_putnbr_base
*/

#include "my.h"

int my_putnbr_base(int nbr, char *base, int pos)
{
    int base_len = my_strlen(base);
    int size = 0;

    if (nbr < 0) {
        nbr *= -1;
        size += my_putchar('-');
    }
    if (nbr == 0 && pos == 0) {
        size += my_putchar('0');
        return (size);
    }
    if (nbr == 0 && pos > 0)
        return (0);
    else {
        pos += 1;
        size += my_putnbr_base(nbr / base_len, base, pos);
    }
    size += my_putchar(base[nbr % base_len]);
    return (size);
}