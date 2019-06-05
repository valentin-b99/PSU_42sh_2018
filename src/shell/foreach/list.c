/*
** EPITECH PROJECT, 2019
** list.c
** File description:
** list
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int add_foreach_var(shell_t *ft, char *var_name)
{
    var_t *var = malloc(sizeof(var_t));

    if (!var)
        return (84);
    find_same_variables(ft, var_name);
    var->name = my_strdup(var_name);
    var->data = NULL;
    var->value = 0;
    var->k = 0;
    var->next = ft->var;
    ft->var = var;
    return (0);
}

void edit_foreach_var(shell_t *ft, char *var_name, char *data)
{
    var_t *var = ft->var;

    while (var) {
        if (!my_strcmp(var->name, var_name)) {
            var->data = my_strdup(data);
            return;
        }
        var = var->next;
    }
}

int fill_list(list_cmd_foreach_t *list_cmd)
{
    char *str = NULL;

    list_cmd->len = 0;
    list_cmd->first = NULL;
    list_cmd->end = NULL;
    write(0, "foreach? ", 9);
    str = get_next_line(0);
    while (str && my_strcmp(str, "end")) {
        if (add_cmd(list_cmd, str))
            return (84);
        write(0, "foreach? ", 9);
        str = get_next_line(0);
    }
    if (!str) {
        write(2, "foreach: end not found.\n", 24);
        return (84);
    }
    free(str);
    return (0);
}

void delete_list_cmd(list_cmd_foreach_t *list_cmd)
{
    cmd_foreach_t *cmd = list_cmd->first;
    cmd_foreach_t *last_cmd = NULL;

    while (cmd) {
        last_cmd = cmd;
        cmd = cmd->next;
        free(last_cmd);
    }
    free(list_cmd);
}