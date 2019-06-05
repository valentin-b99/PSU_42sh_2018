/*
** EPITECH PROJECT, 2019
** replace_var_before_two.c
** File description:
** replace_var_before_two
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

char *var_value_next(var_t *var, char *var_name)
{
    if (!my_strcmp(var->name, var_name)) {
        if (var->k)
            return (my_itoa(var->value));
        else
            return (my_strdup(var->data));
    }
    return (NULL);
}

char *var_value(shell_t *ft, char *str, int len)
{
    var_t *var = ft->var;
    ll_t *env = ft->env;
    char *var_name = my_strdup(str);

    var_name[len] = 0;
    while (var) {
        if (var_value_next(var, var_name))
            return (var_value_next(var, var_name));
        var = var->next;
    }
    while (env) {
        if (!my_strcmp(get_env_name(env->data), var_name))
            return (get_env_data(env->data));
        env = env->next;
    }
    free(var_name);
    return (NULL);
}

char *find_var_and_replace(shell_t *ft, char *str, int *i, int add)
{
    int start_i = *i + 1 + add;
    char *var = NULL;

    *i += 1 + add;
    while (char_in_list(str[*i], LIST_ENV_CHAR))
        *i += 1;
    var = var_value(ft, str + start_i, *i - start_i);
    if (var) {
        str = my_strnncat(start_i - 1 - add, *i + add, str, var);
    } else {
        var = my_strdup(str + start_i);
        var[*i - start_i] = 0;
        var = my_mstrcat(var, ": Undefined variable.\n");
        write(2, var, my_strlen(var));
        ft->rc = 1;
        free(var);
        return (NULL);
    }
    free(var);
    return (str);
}