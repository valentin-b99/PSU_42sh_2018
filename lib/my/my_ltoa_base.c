/*
** EPITECH PROJECT, 2018
** my_ltoa_base
** File description:
** my_ltoa_base
*/

#include "my.h"

void end_ltoa_base(char *str, int neg)
{
    int i = my_strlen(str);

    while (str[--i] == '0')
        str[i] = 0;
    if (neg)
        str[i + 1] = '-';
    my_revstr(str);
}

char *my_ltoa_base(long int nbr, char *str, char *base, int i)
{
    int base_len = my_strlen(base);
    int neg = 0;

    neg = nbr < 0 ? 1 : 0;
    nbr *= neg ? -1 : 1;
    if (nbr == 0) {
        str[i] = '0';
        return (str);
    } else
        my_ltoa_base((long)(nbr / base_len), str, base, i + 1);
    str[i] = base[nbr % base_len];
    if (i == 0)
        end_ltoa_base(str, neg);
    return (str);
}