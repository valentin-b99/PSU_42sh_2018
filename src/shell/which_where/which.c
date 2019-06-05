/*
** EPITECH PROJECT, 2019
** which
** File description:
** which
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int which_is_builtin(char *str)
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
            my_printf("%s: shell built-in command.\n", str);
            return (1);
        }
    }
    return (0);
}

int which_is_alias(shell_t *ft, char *str)
{
    alias_t *tmp = ft->alias;

    while (tmp) {
        if (!my_strncmp(&tmp->alias[6], str, my_strlen(str)) &&
            tmp->alias[6 + my_strlen(str)] == ' ') {
            my_printf("%s:\t aliased to %s\n", str,
                &tmp->alias[6 + my_strlen(str) + 1]);
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int which_is_path(shell_t *ft, char *str)
{
    char *str_access = is_in_path(ft, str);
    struct stat filestat;

    if (!str_access) {
        my_printf("%s: Command not found.\n", str);
        ft->rc = 1;
        return (0);
    }
    lstat(str_access, &filestat);
    if ((filestat.st_mode & __S_IFMT) != __S_IFDIR) {
        my_printf("%s\n", str_access);
        return (rint_free(str_access) | 1);
    }
    ft->rc = 1;
    my_printf("%s: Command not found.\n", str);
    return (rint_free(str_access) | 0);
}

int my_which(shell_t *ft, char **tab)
{
    if (my_tab_size(tab) == 1) {
        ft->rc = 1;
        write(2, "which: Too few arguments.\n", 26);
        return (84);
    }
    for (int i = 1; tab[i]; ++i) {
        if (which_is_alias(ft, tab[i]))
            continue;
        if (which_is_builtin(tab[i]))
            continue;
        which_is_path(ft, tab[i]);
    }
    ft->rc = ft->rc == 1 ? 1 : 0;
    return (0);
}
