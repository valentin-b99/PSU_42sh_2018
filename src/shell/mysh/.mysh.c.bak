/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int forker(shell_t *ft, char *str_access, char **execve_tab, char **env_tab)
{
    pid_t forker = fork();
    int return_valu;

    if (forker) {
        waitpid(forker, &return_valu, 0);
        check_signals(ft, return_valu) == 0 ? ft->rc =
        WEXITSTATUS(return_valu) : 0;
    }
    else
        if (execve(str_access, execve_tab, env_tab) == -1)
            check_return_value(execve_tab, ft);
    return (0);
}

int find_alias(shell_t *ft, char **cmd)
{
    int i = -1;

    while (cmd[++i])
        if (is_an_alias(ft, cmd[i]))
            return (1);
    return (0);
}

int get_access_and_fork(shell_t *ft, char **cmd)
{
    char *str_access = NULL;
    char **env_tab = ll_to_wordtab(ft->env);
    char *str_err = NULL;

    if (!cmd)
        return (free_array(env_tab) | 0);
    if (!(cmd = replace_if_alias(ft, cmd)))
        return (84);
    if (is_builtin(cmd, ft) != -1)
        return (0);
    str_access = is_in_path(ft, cmd[0]);
    if (!str_access) {
        str_err = my_mstrcat(cmd[0], ": Command not found.\n");
        write(2, str_err, my_strlen(str_err));
        ft->rc = 1;
        free(str_err);
    }
    else
        forker(ft, str_access, cmd, env_tab);
    free_array(env_tab);
    return (rint_free(str_access) | 0);
}

int is_builtin(char **cmd, shell_t *ft)
{
    char *cmds[] = { "cd", "env", "setenv", "unsetenv", "exit",
    "alias", "unalias", "echo", "repeat", "which", "where", "foreach",
    "set", "unset", "if", NULL };
    int (*ptrs[])(shell_t *ft, char **tab) = { &my_cd, &my_env, &my_setenv,
    &my_unsetenv, &my_exit, &my_alias, &my_alias, &my_echo, &my_repeat,
    &my_which, &my_where, &my_foreach, &my_set_var, &my_unset_var,
    &my_if, NULL };

    if (!cmd)
        return (-1);
    for (int i = 0; cmds[i]; ++i) {
        if (!my_strcmp(cmds[i], cmd[0]))
            return ((ptrs[i])(ft, cmd));
    }
    return (-1);
}

int mysh(shell_t *ft)
{
    char *path = NULL;
    char *s = NULL;

    while (42) {
        init_struct(ft);
        get_ft(ft);
        s = get_next_line(0);
        if (!s) {
            isatty(0) == 1 ? write(1, "exit\n", 5) : 0;
            exit(ll_free(ft->env) | ll_free_alias(ft->alias) | ft->rc);
        }
        backsticks(ft, &s);
        inhibitors(ft, s);
        replace_vars(ft, &ft->input);
        if (!ft->input || init_tree(ft) == 84)
            continue;
        exec_command(ft, ft->tree);
        free(ft->input);
        free(ft->esc_input);
        free_tree(ft->tree);
        free(path);
    }
    return (0);
}
