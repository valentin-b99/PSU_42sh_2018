/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

char **edit_tab_alias(char **tab, char **cmd, int index)
{
    int i = 2;
    int len = my_strlen_tab(tab);
    char **final = malloc(sizeof(char *) * (len + my_strlen_tab(cmd)));
    int j = 0;
    int k = index;

    while (tab[i]) {
        final[j] = my_strdup(tab[i]);
        i++;
        j++;
    }
    while (cmd[++k]) {
        final[j] = my_strdup(cmd[k]);
        j++;
    }
    final[j] = NULL;
    free_array(tab);
    return (final);
}

int is_an_alias(shell_t *ft, char *str)
{
    char **tab;

    for (alias_t *tmp = ft->alias; tmp; tmp = tmp->next) {
        tab = my_str_to_wordtab(tmp->alias, (char *[]){ " ", "\t", NULL });
        if (!my_strcmp(str, tab[1])) {
            free_array(tab);
            return (1);
        }
    }
    free_array(tab);
    return (0);
}

void freexnull(ll_t **save)
{
    ll_free(*save);
    *save = NULL;
}

char **check_one_alias(shell_t *ft, char **cmd, char **tab, ll_t **save)
{
    for (int i = 0; cmd[i]; i++) {
        if (!my_strcmp(cmd[i], tab[1])) {
            if (alias_find(*save, tab_to_str(&tab[2]))) {
                ft->alias_check = 1;
                printf("Alias loop.\n");
                freexnull(save);
                return (NULL);
            }
            add_alias(save, tab[1]);
            if (tab[2] && is_an_alias(ft, tab[2]) &&
                my_strcmp(tab[2], cmd[i]))
                return (replace_if_alias(ft, edit_tab_alias(tab, cmd, i)));
            freexnull(save);
            ft->alias_check = 1;
            return (edit_tab_alias(tab, cmd, i));
        }
    }
    ft->alias_check = 0;
    return (NULL);
}

char **replace_if_alias(shell_t *ft, char **cmd)
{
    char **tab = NULL;
    char **ret;
    static ll_t *save = NULL;

    for (alias_t *tmp = ft->alias; tmp; tmp = tmp->next) {
        tab = my_str_to_wordtab(tmp->alias, (char *[]){ " ", "\t", NULL });
        if ((ret = check_one_alias(ft, cmd, tab, &save)) == NULL &&
            ft->alias_check) {
            return (NULL);
        } else if (ft->alias_check)
            return (ret);
        free_array(tab);
    }
    ll_free(save);
    save = NULL;
    return (cmd);
}
