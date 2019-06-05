/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int get_str_size(char **tab)
{
    int len = 0;
    int i = 0;
    int j = 0;

    while (tab[i] != NULL) {
        while (tab[i][j] != '\0') {
            len++;
            j++;
        }
        len++;
        i++;
        j = 0;
    }
    return (len);
}

char *tab_to_str(char **tab)
{
    int len = get_str_size(tab);
    char *str = malloc(sizeof(char) * len);
    int j = 0;
    int k = 0;

    if (!str)
        return (NULL);
    for (int i = 0; tab[i]; i++, j = 0, k++) {
        while (tab[i][j] != '\0') {
            str[k] = tab[i][j];
            j++;
            k++;
        }
        str[k] = ' ';
    }
    str[k - 1] = '\0';
    return (str);
}

int save_alias(shell_t *ft, char *str)
{
    alias_t *new = NULL;
    alias_t *tmp = NULL;

    if (!(new = malloc(sizeof(alias_t))))
        return (84);
    tmp = ft->alias;
    new->next = NULL;
    new->alias = my_strdup(str);
    if (tmp == NULL)
        ft->alias = new;
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (0);
}

int find_same_alias(shell_t *ft, char *alias)
{
    alias_t *tmp = ft->alias;
    char **dif = NULL;

    while (tmp) {
        dif = my_str_to_wordtab(tmp->alias, (char *[]){ " ", NULL });
        if (my_strcmp(dif[1], alias) == 0) {
            ll_delete_alias(&ft->alias, tmp);
            strtwt_free_tab(dif);
            break;
        }
        strtwt_free_tab(dif);
        tmp = tmp->next;
    }
    return (0);
}
