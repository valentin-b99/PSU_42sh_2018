/*
** EPITECH PROJECT, 2018
** task07
** File description:
** return the smallest prime number that is greater than
** or equal to the number given as parameter
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    while ((my_is_prime(nb)) != 1) {
        nb = nb + 1;
    }
    return (nb);
}
