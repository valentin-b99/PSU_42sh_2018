/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int pars_if(char **shif, var_t **var)
{
    if (my_strcmp(shif[1], "<") == 0)
        return (lower_op(shif, var));
    if (my_strcmp(shif[1], ">") == 0)
        return (upper_op(shif, var));
    if (my_strcmp(shif[1], "<=") == 0)
        return (lower_op_eg(shif, var));
    if (my_strcmp(shif[1], ">=") == 0)
        return (upper_op_eg(shif, var));
    if (my_strcmp(shif[1], "!=") == 0)
        return (dif_op(shif, var));
    if (my_strcmp(shif[1], "==") == 0)
        return (eg_eg_op(shif, var));
    return (0);
}

char **get_cmd_after_parenthesis(char *str)
{
    int i = 0;
    char **final = NULL;
    char *tmp = NULL;
    int j = 0;

    for (; str[j] != '\0'; j++) {
        if (str[j] == ')') {
            j++;
            break;
        }
    }
    tmp = malloc(sizeof(char) * (my_strlen(str) - j) + 1);
    while (str[j] != '\0') {
        tmp[i] = str[j];
        i++;
        j++;
    }
    tmp[i] = '\0';
    final = my_str_to_wordtab(tmp, (char *[]){ " ", "\t", NULL });
    return (final);
}

int error_if(shell_t *ft, char **shif, char **cmd, char *str)
{
    int len = my_tab_size(shif);

    if (len == 2 || my_strcmp(shif[0], "==") == 0) {
        cmd = get_cmd_after_parenthesis(str);
        if (is_builtin(cmd, ft) != -1);
        else
            get_access_and_fork(ft, cmd);
        return (1);
    }
    if (len == 1) {
        my_printf("if: Empty if.\n");
        return (84);
    }
    if (len != 3) {
        my_printf("if: Expression Syntax.\n");
        return (84);
    }
    return (0);
}

int check_if_op(char **tab)
{
    if (tab[1] == NULL) {
        my_printf("if: Too few arguments.\n");
        return (84);
    }
    return (0);
}

/*int my_if(shell_t *ft, char **tab)
{
    char *str = tab_to_str(tab);
    char *op = get_if_var(str);
    char **shif = my_str_to_wordtab(op, (char *[]){ " ", "\t", NULL });
    char **cmd = NULL;
    var_t *var[2] = { NULL, NULL};
    int i = 0;

    if (check_if_op(tab) == 84 || (i = error_if(ft, shif, cmd, str)) == 84)
        return (84);
    if (i == 1)
        return (0);
    shif[0][0] == '$' ? var[0] = find_ll_variables(ft, shif[0]) : 0;
    shif[2][0] == '$' ? var[1] = find_ll_variables(ft, shif[2]) : 0;
    if (pars_if(shif, var) == 1) {
        cmd = get_cmd_after_parenthesis(str);
        if (is_builtin(cmd, ft) != -1);
        else
            get_access_and_fork(ft, cmd);
    }
    return (0);
}*/

int my_str_isnum_with_add_and_sub(char const *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] != 43 && str[i] != 45 && (str[i] < 48 || str[i] > 57))
            return (0);
    return (1);
}

int parenthesis_error_if(char **str, char **line_if)
{
    int par = 0;

    if ((*str)[0] != '(')
        return (write(2, "if: Expression Syntax.\n", 23));
    for (; (*str)[0]; *str += 1) {
        if ((*str)[0] == '(')
            par++;
        else if ((*str)[0] == ')')
            par--;
        *line_if = my_mstrcat(*line_if, (char [2]){(*str)[0], 0});
        if (!par)
            break;
    }
    *str += 1;
    (*line_if) += 1;
    (*line_if)[my_strlen(*line_if) - 1] = 0;
    if (my_strlen(*line_if) == 0 || my_strlen(*str) == 0)
        return (write(2, "if: Empty if.\n", 14));
    return (0);
}

int correct_comparator(char **tab, char cmp_is_char, int *cmp_id)
{
    char **cmp_num = (char *[7]){"<", ">", "<=", ">=", "==", "!=", NULL};
    char **cmp_txt = (char *[3]){"==", "!=", NULL};

    for (int i = 0; !cmp_is_char && cmp_num[i]; i++) {
        if (!my_strcmp(tab[0], cmp_num[i]))
            *cmp_id = 0;
        else if (!my_strcmp(tab[1], cmp_num[i]))
            *cmp_id = 1;
    }
    if (!cmp_is_char && *cmp_id != -1)
        return (0);
    for (int i = 0; cmp_is_char && cmp_txt[i]; i++)
        if (!my_strcmp(tab[1], cmp_txt[i]))
            return (0);
    return (84);
}

void exec_cmd_if(shell_t *ft, char *str)
{
    int status = 0;
    char *cmd = my_strdup(str);

    if (!fork()) {
        inhibitors(ft, cmd);
        replace_vars(ft, &ft->input);
        if (init_tree(ft) == 84)
            exit (0);
        exec_command(ft, ft->tree);
        free(ft->input);
        free(ft->esc_input);
        free_tree(ft->tree);
        exit (0);
    }
    wait(&status);
    free(cmd);
}

int if_cmp_nb(char **tab, int cmp_id)
{
    if (my_tab_size(tab) == 1)
        return (1);
    if (!my_strcmp(tab[cmp_id], "<") && (((!cmp_id) ? (0) : (my_getnbr(tab[0]))))
    < (((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    if (!my_strcmp(tab[cmp_id], ">") && (((!cmp_id) ? (0) : (my_getnbr(tab[0])))
    > ((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    if (!my_strcmp(tab[cmp_id], "<=") && (((!cmp_id) ? (0) : (my_getnbr(tab[0])))
    <= ((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    if (!my_strcmp(tab[cmp_id], ">=") && (((!cmp_id) ? (0) : (my_getnbr(tab[0])))
    >= ((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    if (!my_strcmp(tab[cmp_id], "==") && (((!cmp_id) ? (0) : (my_getnbr(tab[0])))
    == ((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    if (!my_strcmp(tab[cmp_id], "!=") && (((!cmp_id) ? (0) : (my_getnbr(tab[0])))
    != ((cmp_id && my_tab_size(tab) == 2) ? (0) :
    (my_getnbr(tab[(!cmp_id) ? (1) : (2)])))))
        return (1);
    return (0);
}

int if_cmp_txt(char **tab)
{
    if (!my_strcmp(tab[1], "==") && !my_strcmp(tab[0], tab[2]))
        return (1);
    if (!my_strcmp(tab[1], "!=") && my_strcmp(tab[0], tab[2]))
        return (1);
    return (0);
}

void exec_if(shell_t *ft, char *str, char **tab, char cmp_is_char, int cmp_id)
{
    if (!cmp_is_char && if_cmp_nb(tab, cmp_id))
        exec_cmd_if(ft, str);
    else if (cmp_is_char && if_cmp_txt(tab))
        exec_cmd_if(ft, str);
}

int comparaisons_error_if(shell_t *ft, char *str, char *line_if)
{
    char **tab = my_str_to_wordtab(line_if, (char *[2]){" " , NULL});
    char cmp_is_char = 0;
    int cmp_id = -1;

    if (!tab || !tab[0])
        return (write(2, "if: Expression Syntax.\n", 23));
    if ((my_tab_size(tab) == 3 && (!my_str_isnum_with_add_and_sub(tab[0]) ||
    !my_str_isnum_with_add_and_sub(tab[2]))) || (my_tab_size(tab) == 2 &&
    (tab[0][0] == '<' || tab[0][0] == '>' || tab[0][0] == '!' ||
    tab[0][0] == '=') && !my_str_isnum_with_add_and_sub(tab[1])) ||
    (my_tab_size(tab) == 2 && !my_str_isnum_with_add_and_sub(tab[0]) &&
    (tab[1][0] == '<' || tab[1][0] == '>' || tab[1][0] == '!' ||
    tab[1][0] == '=')))
        cmp_is_char = 1;
    if ((cmp_is_char && my_tab_size(tab) == 2) || my_tab_size(tab) > 3)
        return (write(2, "if: Expression Syntax.\n", 23));
    if ((my_tab_size(tab) >= 2 && correct_comparator(tab, cmp_is_char, &cmp_id))
    || (cmp_is_char && my_tab_size(tab) == 1))
        return (write(2, "if: Expression Syntax.\n", 23));
    exec_if (ft, str, tab, cmp_is_char, cmp_id);
    free_array(tab);
    return (0);
}

int my_if(shell_t *ft, char **tab)
{
    char *line_if = NULL;
    char *str = NULL;

    if (my_tab_size(tab) < 2) {
        write(2, "if: Too few arguments.\n", 23);
        return (set_err_return(ft));
    }
    tab += 1;
    str = tab_to_str(tab);
    if (parenthesis_error_if(&str, &line_if) ||
    comparaisons_error_if(ft, str, line_if))
        return (set_err_return(ft));
    return (0);
}