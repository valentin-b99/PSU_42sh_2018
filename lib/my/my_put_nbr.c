/*
** EPITECH PROJECT, 2018
** my_put_nbr
** File description:
** displays the number given as a parameter. It must be able
** to display all the possible values of an int
*/

#include "my.h"

int my_put_nbr(int nb)
{
    int mod;
    int size = 0;

    if (nb == -2147483648){
        write(1, "-2147483648", 11);
        size += 11;
        return (size);
    }
    if (nb < 0){
        size += my_putchar('-');
        nb = nb * (-1);
    }
    if (nb >= 10){
        mod = nb % 10;
        nb = (nb - mod) / 10;
        size += my_put_nbr(nb);
        size += my_putchar((mod % 10) + 48);
    } else
        size += my_putchar(nb + 48);
    return (size);
}
