/*
** EPITECH PROJECT, 2019
** my_itoa.c
** File description:
** my_itoa
*/

#include "my.h"

char *my_itoa(int nb)
{
    char *result = malloc(sizeof(char) * 11);
    int i = 0;
    int neg = 1;

    if (nb == 0)
        return ("0");
    if (nb < 0) {
        neg = -1;
        nb = nb * (-1);
    }
    while (nb != 0) {
        result[i] = (nb % 10) + 48;
        nb = nb /10;
        i++;
    }
    if (neg == -1) {
        result[i] = '-';
        i++;
    }
    result[i] = 0;
    return (my_revstr(result));
}