/*
** EPITECH PROJECT, 2018
** task01
** File description:
** swaps the content of two integers
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
