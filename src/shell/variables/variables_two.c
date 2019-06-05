/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int var_data_value(shell_t *ft, var_t *new)
{
    new->name = my_strdup(ft->variables[0]);
    if (ft->variables[2] != NULL) {
        new->data = my_strdup(ft->variables[2]);
        new->k = 0;
        new->value = 0;
        return (0);
    }
    if (ft->variables[1] != NULL) {
        new->value = my_getnbr(ft->variables[1]);
        new->k = 1;
        new->data = NULL;
        return (0);
    }
    return (0);
}

int save_variables(shell_t *ft)
{
    var_t *new = NULL;
    var_t *tmp = NULL;

    if ((new = malloc(sizeof(var_t))) == NULL)
        return (84);
    tmp = ft->var;
    new->next = NULL;
    var_data_value(ft, new);
    if (tmp == NULL)
        ft->var = new;
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (0);
}

char *copy_str(char *buff, int i)
{
    char *tmp = NULL;
    int k = 0;

    if ((tmp = x_memset(0, my_strlen(buff) + 1, sizeof(char))) == NULL)
        return (NULL);
    while (buff[i] != '\0' && (buff[i] != '"' && buff[i] != '\'')) {
        tmp[k] = buff[i];
        i += 1;
        k += 1;
    }
    return (tmp);
}

int find_str(shell_t *ft, char *buff)
{
    int i = 0;

    for (i = 0; buff[i] != '\0'; i += 1) {
        if (buff[i] == '"' || buff[i] == '\'') {
            i += 1;
            ft->variables[2] = copy_str(buff, i);
            return (1);
        }
    }
    return (0);
}

int ll_delete_variables(var_t **head, var_t *node)
{
    var_t *tmp = *head;
    var_t *temp = NULL;

    if (!head || !(*head) || !node)
        return (84);
    while (tmp && tmp != node) {
        temp = tmp;
        tmp = tmp->next;
    }
    if (tmp == *head)
        *head = tmp->next;
    else
        temp->next = tmp->next;
    tmp->data ? free(tmp->data) : 0;
    tmp->name ? free(tmp->name) : 0;
    tmp ? free(tmp) : 0;
    return (0);
}