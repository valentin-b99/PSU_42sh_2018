/*
** EPITECH PROJECT, 2019
** foreach
** File description:
** foreach
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int add_cmd(list_cmd_foreach_t *list_cmd, char *str)
{
    cmd_foreach_t *cmd = malloc(sizeof(cmd_foreach_t));

    if (!cmd)
        return (84);
    cmd->cmd = my_strdup(str);
    cmd->next = NULL;
    if (!list_cmd->first)
        list_cmd->first = cmd;
    if (!list_cmd->end)
        list_cmd->end = cmd;
    else
        list_cmd->end->next = cmd;
    list_cmd->len += 1;
    return (0);
}

void exec_foreach_cmd_next(shell_t *ft, cmd_foreach_t *cmd)
{
    while (cmd) {
        while (cmd && !cmd->cmd)
            cmd = cmd->next;
        if (!cmd)
            return;
        inhibitors(ft, cmd->cmd);
        replace_vars(ft, &ft->input);
        if (init_tree(ft) == 84)
            continue;
        exec_command(ft, ft->tree);
        cmd = cmd->next;
    }
}

void exec_foreach_cmd(shell_t *ft, list_cmd_foreach_t *list_cmd)
{
    cmd_foreach_t *cmd = list_cmd->first;
    int status = 0;

    if (!fork()) {
        exec_foreach_cmd_next(ft, cmd);
        free(ft->input);
        free(ft->esc_input);
        free_tree(ft->tree);
        exit (0);
    }
    wait(&status);
}

void exec_foreach(shell_t *ft, char **tab, list_cmd_foreach_t *list_cmd,
char *var_name)
{
    for (int i = 0; tab[i]; i++) {
        edit_foreach_var(ft, var_name, tab[i]);
        exec_foreach_cmd(ft, list_cmd);
    }
}

int my_foreach(shell_t *ft, char **tab)
{
    char *var_name = my_strdup(tab[1]);
    list_cmd_foreach_t *list_cmd = malloc(sizeof(list_cmd_foreach_t));

    if (!list_cmd)
        return (set_err_return(ft));
    if (my_tab_size(tab) < 3) {
        write(2, "foreach: Too few arguments.\n", 28);
        return (set_err_return(ft));
    }
    tab += 2;
    if (parenthesis_error(tab))
        return (set_err_return(ft));
    if (fill_list(list_cmd) || add_foreach_var(ft, var_name))
        return (set_err_return(ft));
    exec_foreach(ft, tab, list_cmd, var_name);
    free(var_name);
    delete_list_cmd(list_cmd);
    return (0);
}