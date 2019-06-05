/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

char *cpy_op(int i, char *str)
{
    char *op = x_memset(0, my_strlen(str), sizeof(char));
    int k = 0;

    if (!op)
        return (NULL);
    for (; str[i] != '\0' && str[i] != ')'; i += 1) {
        op[k] = str[i];
        k += 1;
    }
    return (op);
}

char *get_if_var(char *str)
{
    char *op = NULL;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '(') {
            i += 1;
            op = cpy_op(i, str);
        }
    }
    return (op);
}

int dif_op(char **shif, var_t **var)
{
    if (dif_op_var(var, shif) == 1)
        return (1);
    if (var[0] == NULL && var[1] != NULL) {
        if (var[1]->k == 1 && my_str_isnum(shif[0]) == 1) {
            if (var[1]->value != my_getnbr(shif[0]))
                return (1);
        }
        if (var[1]->k == 0 && my_str_isnum(shif[0]) == 0) {
            if (my_strcmp(var[0]->data, shif[0]) == 1)
                return (1);
        }
    }
    if (var[0] == NULL && var[1] == NULL) {
        if (my_str_isnum(shif[0]) == 1 && my_str_isnum(shif[2]) == 1) {
            if (my_getnbr(shif[0]) != my_getnbr(shif[2]))
                return (1);
        }
        else if (my_strcmp(shif[0], shif[2]) != 0)
            return (1);
    }
    return (0);
}