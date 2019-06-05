/*
** EPITECH PROJECT, 2018
** task05
** File description:
** return the square root of the number if it's
** a whole number or 0 if not
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int result;

    result = 0;
    if (nb < 0)
        return (0);
    while (result * result != nb) {
        if (result == nb)
            return (0);
        result = result + 1;
    }
    return (result);
}
