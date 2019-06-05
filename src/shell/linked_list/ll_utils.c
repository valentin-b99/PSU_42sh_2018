/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int add_list(shell_t *ft, char *env)
{
    ll_t *element = malloc(sizeof(ll_t));
    ll_t *tmp = ft->env;

    if (!element)
        return (84);
    element->next = NULL;
    element->data = my_strdup(env);
    if (tmp == NULL)
        ft->env = element;
    else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = element;
    }
    return (0);
}

int env_to_ll(shell_t *ft, char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        add_list(ft, env[i]);
        i++;
    }
    return (0);
}

int ll_free(ll_t *head)
{
    if (head) {
        if (head->next)
            ll_free(head->next);
        if (head->data)
            free(head->data);
        free(head);
    }
    return (0);
}

char **ll_to_wordtab(ll_t *head)
{
    ll_t *tmp = head;
    int elems = 0;
    char **result = NULL;

    while (tmp) {
        elems += 1;
    tmp = tmp->next;
    }
    if (!(result = malloc(sizeof(char *) * (elems + 1))))
        return (NULL);
    result[elems] = NULL;
    tmp = head;
    for (int i = 0; i < elems; ++i) {
        result[i] = my_strdup(tmp->data);
        tmp = tmp->next;
    }
    return (result);
}

char *ll_find(ll_t *head, char *data)
{
    ll_t *tmp = head;
    int len = my_strlen(data);
    char *result = NULL;

    if (!tmp || !data)
        return (NULL);
    while (tmp) {
        if (!my_strncmp(tmp->data, data, len) && tmp->data[len] == '=') {
            result = my_strdup(tmp->data + len + 1);
            return (result);
        }
        tmp = tmp->next;
    }
    return (NULL);
}
