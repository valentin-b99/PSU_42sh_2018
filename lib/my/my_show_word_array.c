/*
** EPITECH PROJECT, 2018
** my_show_word_array
** File description:
** from array to string
*/

#include "my.h"

int my_show_word_array(char * *tab)
{
    for (int i = 0; tab[i] != 0; ++i) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return (0);
}
