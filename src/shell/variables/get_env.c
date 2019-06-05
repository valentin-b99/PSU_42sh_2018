/*
** EPITECH PROJECT, 2019
** get_env.c
** File description:
** get_env
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

char *get_env_name(char *data)
{
    int i = 0;
    char *result = my_strdup(data);

    while (result[i] != '=')
        i++;
    result[i] = 0;
    return (result);
}

char *get_env_data(char *data)
{
    char *result = NULL;

    while (data[0] != '=')
        data += 1;
    data += 1;
    if ((result = malloc(sizeof(char) * (my_strlen(data) + 1))) == NULL)
        return (NULL);
    result = my_strcpy(result, data);
    return (result);
}