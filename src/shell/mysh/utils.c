/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int free_array(char **tab)
{
    int i = 0;

    if (!tab)
        return (0);
    while (tab[i]) {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}

int display_array(char **tab)
{
    int i = 0;

    while (tab[i]) {
        my_printf("%s\n", tab[i]);
        i++;
    }
    return (0);
}

void *cmdu_free_return(void *ptr, char **tab, void *ret)
{
    char *tmp = ret ? my_strdup((char *)ret) : NULL;

    free(ptr);
    strtwt_free_tab(tab);
    return (tmp);
}

char *is_in_path(shell_t *ft, char *cmd)
{
    char *path = ll_find(ft->env, "PATH");
    char **path_tab = my_str_to_wordtab(path, (char*[]){ ":", NULL });

    if (!path || !path_tab)
        return (NULL);
    if (!access(cmd, X_OK))
        return (cmdu_free_return(path, path_tab, cmd));
    if (my_strstr(cmd, "/"))
        return (cmdu_free_return(path, path_tab, NULL));
    for (int i = 0; path_tab[i]; ++i) {
        if (!(path_tab[i] = my_realloc(path_tab[i],
            my_strlen(path_tab[i]) + my_strlen(cmd) + 1)))
            return (cmdu_free_return(path, path_tab, NULL));
        my_strcat(path_tab[i], "/");
        my_strcat(path_tab[i], cmd);
        if (!access(path_tab[i], X_OK))
            return (cmdu_free_return(path, path_tab, path_tab[i]));
    }
    return (cmdu_free_return(path, path_tab, NULL));
}

int print_array(char **tab)
{
    int i = 0;

    while (tab[i]) {
        my_printf("%s\n", tab[i]);
        i++;
    }
    return (0);
}
