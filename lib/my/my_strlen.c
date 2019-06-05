/*
** EPITECH PROJECT, 2018
** task03
** File description:
** return the number of characters found in the string passed in parameters
*/

#include "my.h"

int my_strlen(char *str)
{
    int counter = 0;

    if (!str)
        return (0);
    while (str[counter] != '\0') {
        counter = counter + 1;
    }
    return (counter);
}
