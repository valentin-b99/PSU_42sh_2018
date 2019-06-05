/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int ll_update_node(shell_t *ft, ll_t **head, char *data, char *new)
{
    ll_t *tmp = *head;
    int len = my_strlen(data);

    if (!data)
        return (84);
    while (tmp) {
        if (!(my_strncmp(tmp->data, data, len)) && tmp->data[len] == '=') {
            my_memset(tmp->data + len + 1, 0, my_strlen(tmp->data) - (len + 1));
            tmp->data = my_realloc(tmp->data,
                my_strlen(tmp->data) + (new ? my_strlen(new) : 1));
            new ? my_strcat(tmp->data, new) : 0;
            return (0);
        }
        tmp = tmp->next;
    }
    ll_update_node_two(ft, data, new);
    return (0);
}

int ll_update_node_two(shell_t *ft, char *data, char *new)
{
    char *add = x_memset(0, my_strlen(data) +
        (new ? my_strlen(new) : 1) + 1, sizeof(char));

    my_strcpy(add, data);
    my_strcat(add, "=");
    new ? my_strcat(add, new) : 0;
    add_list(ft, add);
    return (rint_free(add) | 0);
}

int ll_remove_node(ll_t **head, ll_t *node)
{
    ll_t *tmp = *head;
    ll_t *temp = NULL;

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
    tmp ? free(tmp) : 0;
    return (0);
}
