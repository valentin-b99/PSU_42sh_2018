/*
** EPITECH PROJECT, 2018
** task04
** File description:
** recursive function that returns the first argument raised
** to the power of the second argument
*/

#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    nb = nb * my_compute_power_rec(nb, p - 1);
    p = p - 1;
    return (nb);
}
