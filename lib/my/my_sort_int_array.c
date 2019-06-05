/*
** EPITECH PROJECT, 2018
** task06
** File description:
** sort an integer array in ascending order
*/

#include "my.h"

void my_sort_int_array(int *array, int size)
{
    int i = -1;
    int tmp = size;

    while (++i < tmp) {
        if (i == tmp - 1)
            tmp -= 1;
        else if (array[i + 1] < array[i]) {
            array[i] ^= array[i + 1];
            array[i + 1] ^= array[i];
            array[i] ^= array[i + 1];
            i = -1;
        }
    }
}
