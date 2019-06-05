/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int check_alias(shell_t *ft, char *alias)
{
    int count = 0;
    int i = 0;
    char **tab = my_str_to_wordtab(alias, (char *[]){ "\t", " ", NULL });

    for (int j = 0; alias[j]; j++)
        if (alias[j] == '"') {
            count++;
            alias[j] = ' ';
        }
    if (count % 2) {
        my_printf("Unmatched '\"'.\n");
        free_array(tab);
        return (84);
    }
    for (i = 0; tab[i] != NULL; i += 1);
    if (i < 3)
        return (84);
    find_same_alias(ft, tab[1]);
    save_alias(ft, alias);
    return (strtwt_free_tab(tab) | 0);
}

int delete_alias(shell_t *ft, char *dif)
{
    alias_t *tmp = ft->alias;
    char **tab =  NULL;

    while (tmp) {
        tab = my_str_to_wordtab(tmp->alias, (char *[]){ "\t", " ", NULL });
        if (my_strncmp(tab[1], dif, my_strlen(dif)) == 0) {
            ll_delete_alias(&ft->alias, tmp);
            strtwt_free_tab(tab);
            return (0);
        }
        strtwt_free_tab(tab);
        tmp = tmp->next;
    }
    tab ? strtwt_free_tab(tab) : 0;
    return (0);
}

int find_and_delete_alias(shell_t *ft, char *alias)
{
    char **tab = my_str_to_wordtab(alias, (char *[]){ "\t", " ", NULL });

    for (int i = 1; tab[i] != NULL; i += 1)
        delete_alias(ft, tab[i]);
    strtwt_free_tab(tab);
    return (0);
}

int ll_delete_alias(alias_t **head, alias_t *node)
{
    alias_t *tmp = *head;
    alias_t *temp = NULL;

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
    tmp->alias ? free(tmp->alias) : 0;
    tmp ? free(tmp) : 0;
    return (0);
}
