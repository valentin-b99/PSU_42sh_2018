/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int ll_free_alias(alias_t *head)
{
    if (head) {
        if (head->next)
            ll_free_alias(head->next);
        if (head->alias)
            free(head->alias);
        free(head);
    }
    return (0);
}
