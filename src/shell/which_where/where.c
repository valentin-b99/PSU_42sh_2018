/*
** EPITECH PROJECT, 2019
** where
** File description:
** where
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int where_is_builtin(char *str)
{
    char *builtin[] = { ":", "@", "alias", "alloc", "bg", "bindkey", "break",
        "breaksw", "builtins", "case", "cd", "chdir", "complete", "continue",
        "default", "dirs", "echo", "echotc", "else", "end", "endif", "endsw",
        "eval", "exec", "exit", "fg", "filetest", "foreach", "glob", "goto",
        "hashstat", "history", "hup", "if", "jobs", "kill", "limit", "log",
        "login", "logout", "ls-F", "nice", "nohup", "notify", "onintr", "popd",
        "printenv", "pushd", "rehash", "repeat", "sched", "set", "setenv",
        "settc", "setty", "shift", "source", "stop", "suspend", "switch",
        "telltc", "termname", "time", "umask", "unalias", "uncomplete",
        "unhash", "unlimit", "unset", "unsetenv", "wait", "where", "which",
        "while", NULL };

    for (int i = 0; builtin[i]; ++i) {
        if (!my_strcmp(builtin[i], str)) {
            my_printf("%s is a shell built-in\n", str);
            return (1);
        }
    }
    return (0);
}

int where_is_alias(shell_t *ft, char *str)
{
    alias_t *tmp = ft->alias;

    while (tmp) {
        if (!my_strncmp(&tmp->alias[6], str, my_strlen(str)) &&
            tmp->alias[6 + my_strlen(str)] == ' ') {
            my_printf("%s is aliased to %s\n", str,
                &tmp->alias[6 + my_strlen(str) + 1]);
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int where_is_path(shell_t *ft, char *str)
{
    char *path = ll_find(ft->env, "PATH");
    char **pt = my_str_to_wordtab(path, (char*[]){ ":", NULL });
    char *str_access = is_in_path(ft, str);
    struct stat filestat;

    str_access ? lstat(str_access, &filestat) : 0;
    if (!str_access || (filestat.st_mode & __S_IFMT) == __S_IFDIR)
        return (rint_free(path) | free_array(pt) | (ft->rc = 1));
    for (int i = 0; pt[i]; ++i) {
        if (!(pt[i] = my_realloc(pt[i],
            my_strlen(pt[i]) + my_strlen(str) + 1)))
            return (rint_free(path) | free_array(pt) | rint_free(str_access)
                | (ft->rc = 1));
        pt[i][my_strlen(pt[i]) - 1] != '/' ? my_strcat(pt[i], "/") : 0;
        my_strcat(pt[i], str);
        if (!access(pt[i], X_OK))
            my_printf("%s\n", pt[i]);
    }
    return (rint_free(str_access) | rint_free(path) | free_array(pt));
}

int my_where(shell_t *ft, char **tab)
{
    if (my_tab_size(tab) == 1) {
        write(2, "where: Too few arguments.\n", 26);
        ft->rc = 1;
        return (84);
    }
    for (int i = 1; tab[i]; ++i) {
        if (my_strstr(tab[i], "/")) {
            write(2, "where: / in command makes no sense\n", 35);
            ft->rc = 1;
            continue;
        }
        where_is_alias(ft, tab[i]);
        where_is_builtin(tab[i]);
        where_is_path(ft, tab[i]);
    }
    ft->rc = ft->rc == 1 ? 1 : 0;
    return (0);
}
