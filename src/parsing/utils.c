/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int print_int_array(int *array)
{
    int i = 0;

    while (array[i] != -1) {
        my_printf("%d\n", array[i]);
        i++;
    }
    return (0);
}
