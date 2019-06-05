/*
** EPITECH PROJECT, 2018
** my_strtol
** File description:
** my_strtol
*/

#include "my.h"

long int my_strtol(char *str, char **endptr)
{
    int i = -1;
    int sign = 0;
    long int nbr = 0;

    while (str[++i] == '-' || str[i] == '+')
        sign += str[i] == '-' ? 1 : 0;
    sign = sign % 2 == 0 ? 1 : 0;
    i -= 1;
    while (str[++i] >= '0' && str[i] <= '9')
        nbr = (nbr * 10) + (str[i] - 48);
    *endptr = str + i;
    nbr *= sign ? 1 : -1;
    return (nbr);
}