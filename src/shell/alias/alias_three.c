/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int alias_find(ll_t *alias, char *data)
{
    while (alias) {
        if (alias->data && !my_strcmp(alias->data, data)) {
            free(data);
            return (1);
        }
        alias = alias->next;
    }
    free(data);
    return (0);
}

int add_alias(ll_t **head, char *data)
{
    ll_t *element = malloc(sizeof(ll_t));
    ll_t *tmp = *head;

    if (!element)
        return (84);
    element->next = NULL;
    element->data = my_strdup(data);
    if (tmp == NULL)
        *head = element;
    else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = element;
    }
    return (0);
}

int my_alias(shell_t *ft, char **tab)
{
    char *alias = NULL;

    if ((alias = tab_to_str(tab)) == NULL)
        return (84);
    if ((my_strncmp(tab[0], "alias", 5)) == 0) {
        if (check_alias(ft, alias) == 84)
            return (84);
    }
    if ((my_strncmp(tab[0], "unalias", 7)) == 0)
        find_and_delete_alias(ft, alias);
    free(alias);
    return (0);
}

void display_ll_alias(shell_t *ft)
{
    for (alias_t *tmp = ft->alias; tmp; tmp = tmp->next)
        my_printf("%s\n", tmp->alias);
}
