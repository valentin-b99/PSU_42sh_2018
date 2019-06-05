/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int my_cd(shell_t *ft, char **tab)
{
    if (tab[1] && tab[2]) {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Too many arguments.\n", 22);
        ft->rc = 1;
        return (84);
    }
    if (tab[1] && !my_strncmp(tab[1], "~/", 2)) {
        if (my_cd_home(ft, tab))
            return (ft->rc);
        return (my_cd_path(ft, tab));
    }
    if (!tab[1] || !my_strncmp(tab[1], "--", 2) || !my_strncmp(tab[1], "~", 1)
        || !my_strncmp(tab[1], "home", 4))
        return (my_cd_home(ft, tab));
    else if (!my_strncmp(tab[1], "-", 1))
        return (my_cd_oldpwd(ft, tab));
    else
        return (my_cd_path(ft, tab));
    return (0);
}

int my_cd_error(char *str, int error, shell_t *ft)
{
    char *err = strerror(error);

    write(2, str ? str : "", str ? my_strlen(str) : 0);
    write(2, ": ", 2);
    write(2, err, my_strlen(err));
    write(2, ".\n", 2);
    ft->rc = 1;
    return (84);
}

int my_cd_home(shell_t *ft, char **tab)
{
    char *home = ll_find(ft->env, "HOME");
    char cwd[256];

    if (!getcwd(cwd, sizeof(cwd)) || (home && chdir(home) != 0))
        return (my_cd_error(tab[1], errno, ft));
    ll_update_node(ft, &ft->env, "OLDPWD", cwd);
    if (my_memset(cwd, 0, 256) && !getcwd(cwd, sizeof(cwd)))
        return (my_cd_error(tab[1], errno, ft));
    if (tab[1] && !my_strcmp(tab[1], "home"))
        write(1, "~\n", 2);
    ll_update_node(ft, &ft->env, "PWD", cwd);
    home ? free(home) : 0;
    ft->fcd = 0;
    ft->rc = 0;
    return (0);
}

int my_cd_oldpwd(shell_t *ft, char **tab)
{
    char *old = ll_find(ft->env, "OLDPWD");
    char *current = ll_find(ft->env, "PWD");
    int rc = 0;

    if (ft->fcd) {
        write(2, ": No such file or directory.\n", 29);
        ft->rc = 1;
        rc = 1;
    } else if (!ft->fcd && old && chdir(old) != 0) {
        my_cd_error(tab[1], errno, ft);
        old ? free(old) : 0;
        current ? free(current) : 0;
        return (84);
    }
    !ft->fcd ? ll_update_node(ft, &ft->env, "OLDPWD", current) : 0;
    !ft->fcd ? ll_update_node(ft, &ft->env, "PWD", old) : 0;
    old ? free(old) : 0;
    current ? free(current) : 0;
    return (rc);
}

int my_cd_path(shell_t *ft, char **tab)
{
    char cwd[256];
    char *data = NULL;

    if (!getcwd(cwd, sizeof(cwd)))
        return (my_cd_error(tab[1], errno, ft));
    data = x_memset(0, my_strlen(cwd) + my_strlen(tab[1]) + 1, sizeof(char));
    my_strcpy(data, cwd);
    data[my_strlen(data)] != '/' ? my_strcat(data, "/") : 0;
    my_strcat(data, !my_strncmp(tab[1], "~/", 2) ? tab[1] + 2 : tab[1]);
    ll_update_node(ft, &ft->env, "OLDPWD", cwd);
    if (my_memset(cwd, 0, 256) && (chdir(tab[1][0] == '/' ? tab[1] : data)
        != 0 || !getcwd(cwd, sizeof(cwd)))) {
        data ? free(data) : 0;
        return (my_cd_error(tab[1], errno, ft));
    }
    ll_update_node(ft, &ft->env, "PWD", cwd);
    data ? free(data) : 0;
    ft->fcd = 0;
    ft->rc = 0;
    return (0);
}
