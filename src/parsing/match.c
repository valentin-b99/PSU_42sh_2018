/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** match
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

char *newcat(char *str, char *to_cat)
{
    if (str == NULL)
        return (my_strdup(to_cat));
    char *ret = malloc(sizeof(char) *
        (my_strlen(str) + my_strlen(to_cat) + 1));

    my_strcpy(ret, str);
    my_strcat(ret, to_cat);
    free(str);
    return (ret);
}