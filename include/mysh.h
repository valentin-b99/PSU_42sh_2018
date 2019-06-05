/*
** EPITECH PROJECT, 2019
** mysh
** File description:
** mysh
*/

#ifndef MYSH_H_
# define MYSH_H_

# include "./my.h"
# include <unistd.h>
# include <sys/sysmacros.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <glob.h>

# define ABS(i) i < 0 ? i * -1 : i
# define LIST_ENV_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef int (*ptr_fct_t)(char const *name, char const *to_match);

typedef struct cmd_foreach_s
{
    char *cmd;
    struct cmd_foreach_s *next;
} cmd_foreach_t;

typedef struct list_cmd_foreach_s
{
    int len;
    cmd_foreach_t *first;
    cmd_foreach_t *end;
} list_cmd_foreach_t;

typedef struct s_ll {
    char *data;
    struct s_ll *next;
} ll_t;

typedef struct s_tree {
    char *name;
    char *hidden;
    int check;
    int return_val;
    int if_each_check;
    struct s_tree *left;
    struct s_tree *right;
    struct s_tree *parent;
} tree_t;

typedef struct s_alias {
    char *alias;
    struct s_alias *next;
} alias_t;

typedef struct s_var {
    char *data;
    char *name;
    int value;
    int k;
    struct s_var *next;
} var_t;

typedef struct s_shell {
    struct s_tree *tree;
    struct s_ll *env;
    struct s_alias *alias;
    struct s_var *var;
    char **tab;
    char *input;
    char *esc_input;
    char *left;
    char *right;
    char *variables[3];
    char *stvar[4];
    int is_var;
    int flag_n;
    int rc;
    int empty;
    int prio;
    int fail;
    int fcd;
    int old_fd;
    int right_redir;
    int left_redir;
    int alias_check;
    int if_check;
} shell_t;

/* ---------------------------------------------- */
/* PARSING */

/* assign_str.c */
int assign_left_right(shell_t *ft, int i, int check);
int assign_str_branch(shell_t *ft, int i);

/* quote.c */
int count_quote(shell_t *ft);
int found_close_quote(shell_t *ft, int i);
int *found_where_ignore_quote(shell_t *ft);
int epure_quote_tree(tree_t *leaf);

/* free.c */
int rint_free(void *ptr);
int free_tree(tree_t *tree);

/* globbing.c */
int contains(char *str, char *proc);
int check_str(char *str);
int call_glob(int *nb, char **str, glob_t *paths);
char *newcat(char *str, char *to_cat);
char *check_glob(char *str);

/* match.c */

int match(char const *s1, char const *s2);
int cmatch(char const *name, char const *to_match);

/* parenthesis_utils.c */
int check_if_parenthesis(char *str);
int found_last_open_parenthesis(shell_t *ft);
int count_open_parenthesis(shell_t *ft);
int found_good_close_parenthesis(shell_t *ft, int i);

/* parenthesis.c */
int *found_where_ignore(shell_t *ft);
int check_parenthesis(shell_t *ft);

/* parsing_errors_one.c */
int analyse_command(shell_t *ft, tree_t *leaf);
int found_tree_errors(shell_t *ft, tree_t *leaf);

/* parenthesis_errors_two.c */
int check_double_redir_errors(shell_t *ft, int i, tree_t *leaf, int check);
int check_left_error(shell_t *ft, int i, tree_t *leaf);
int check_right_error(shell_t *ft, int i, tree_t *leaf);
int check_double_way_errors(shell_t *ft, int i, tree_t *leaf);
int check_error_delim(shell_t *ft, int i, tree_t *leaf);

/* split_input.c */
int check_need_ignore_it(int *array, int i);
int parse_str_to_found(shell_t *ft, char *delim);
int found_priorities(shell_t *ft);
char *assign_root(shell_t *ft, int i);
int parse_input(shell_t *ft, tree_t *leaf);

/* traversal_two.c */
int parse_tree_str_two(char *ll_name, char *delim);
int parse_tree_str_three(char *ll_name, char *delim);
int parse_tree_str(char *ll_name, int current, char *delim);

/* traversal.c */
int check_redir(tree_t *leaf);
int inorder(shell_t *ft, tree_t *leaf);
int found_if_just_separator(char *leaf_name);

/* tree.c */
tree_t *root_tree(char *root);
int add_leaf(tree_t *leaf, char *left, char *right, char *root);
int print_tree_prefix(tree_t *tr);

/* utils.c */
int print_int_array(int *array);

/* backsticks.c */
void backsticks(shell_t *ft, char **c);
int error_backsticks(char *cmd);
char *create_ret(char *cmd, int pos, int i, char *output);

/* exec_backsticks */
void init_exec_backstick(shell_t *n);
void exec_str(shell_t *n, char *cmd, shell_t *ft);
char *exec_backsticks(shell_t *ft, char *cmd);

/* ---------------------------------------------- */

/* SHELL */

/* varriables_utils.c */
int get_idx_from_addr(char *str, char *addr);
int remove_cote(char *str);

/* SHELL/ALIAS */

/* alias_three.c */
int my_alias(shell_t *ft, char **tab);
void display_ll_alias(shell_t *ft);
int alias_find(ll_t *alias, char *data);
int add_alias(ll_t **head, char *data);

/* alias_two.c */
int check_alias(shell_t *ft, char *alias);
int delete_alias(shell_t *ft, char *dif);
int find_and_delete_alias(shell_t *ft, char *alias);
int ll_delete_alias(alias_t **head, alias_t *node);

/* alias.c */
int get_str_size(char **tab);
char *tab_to_str(char **tab);
int save_alias(shell_t *ft, char *str);
int find_same_alias(shell_t *ft, char *alias);

/* ---------------------------------------------- */
/* SHELL/BUILTINS */

/* builtins.c */
int my_env(shell_t *ft, __attribute__ ((unused)) char **tab);
int my_unsetenv(shell_t *ft, char **tab);
int my_setenv(shell_t *ft, char **tab);
int my_setenv_two(shell_t *ft, char **tab);
int my_exit(shell_t *ft, char **tab);

/* echo.c */
int char_in_list(char c, char *list_char);
char *echo_tab_to_str(char **tab, char *str);
int echo_error(shell_t *ft, char ***tab, int *new_line);
char *replace_backslash(char *str);
int my_echo(shell_t *ft, char **tab);

/* my_cd.c */
int my_cd(shell_t *ft, char **tab);
int my_cd_error(char *str, int error, shell_t *ft);
int my_cd_home(shell_t *ft, char **tab);
int my_cd_oldpwd(shell_t *ft, char **tab);
int my_cd_path(shell_t *ft, char **tab);

/* repeat.c */
int my_repeat(shell_t *ft, char **tab);

/* ---------------------------------------------- */
/* SHELL/DUP */

/* pipes.c */
void my_exec_pipe(shell_t *ft, tree_t *leaf);
void pipe_function_exec(shell_t *ft, tree_t *leaf);
int pipe_function(shell_t *ft, tree_t *leaf, int save_in, int save_out);
void set_saves_pipes(tree_t *leaf, int *save_in, int *save_out);

/* redirections_left.c */
int left_side(shell_t *ft, char *file, tree_t *leaf);
int double_left_redir_end(shell_t *ft, char *target);
int double_left_redir(shell_t *ft, char *target);

/* redirections_right.c */
int right_side(shell_t *ft, char *file, tree_t *leaf);

/* redirections_utils.c */
int clean_redir_two(shell_t *ft, tree_t *leaf);
int clean_redir(shell_t *ft, tree_t *leaf);
int check_if_already_redir(shell_t *ft);

/* ---------------------------------------------- */
/* SHELL/IF */

/* if_two.c */
char *cpy_op(int i, char *str);
char *get_if_var(char *str);
int dif_op(char **shif, var_t **var);

/* if.c */
int pars_if(char **shif, var_t **var);
char **get_cmd_after_parenthesis(char *str);
int error_if(shell_t *ft, char **shif, char **cmd, char *str);
int check_if_op(char **tab);
int my_if(shell_t *ft, char **tab);

/* operators_for.c */
int upper_op(char **shif, var_t **var);
int lower_op_eg_var_two(var_t **var);
int lower_op_eg_var(var_t **var, char **shif);

/* operators_three.c */
int lower_op_var_two(var_t **var);
int lower_op_var(var_t **var, char **shif);
int lower_op(char **shif, var_t **var);
int upper_op_var_two(var_t **var);
int upper_op_var(var_t **var, char **shif);

/* operators_two.c */
int lower_op_eg(char **shif, var_t **var);
int upper_op_eg_var_two(var_t **var);
int upper_op_eg_var(var_t **var, char **shif);
int upper_op_eg(char **shif, var_t **var);

/* operators.c */
int eg_op_var_two(var_t **var);
int eg_op_var(var_t **var, char **shif);
int eg_eg_op(char **shif, var_t **var);
int dif_op_var_two(var_t **var);
int dif_op_var(var_t **var, char **shif);

/* ---------------------------------------------- */
/* SHELL/FOREACH */

/* errors.c */
int set_err_return(shell_t *ft);
int parenthesis_error(char **tab);

/* foreach.c */
int add_cmd(list_cmd_foreach_t *list_cmd, char *str);
void exec_foreach_cmd_next(shell_t *ft, cmd_foreach_t *cmd);
void exec_foreach_cmd(shell_t *ft, list_cmd_foreach_t *list_cmd);
void exec_foreach(shell_t *ft, char **tab, list_cmd_foreach_t *list_cmd,
char *var_name);
int my_foreach(shell_t *ft, char **tab);

/* list.c */
int add_foreach_var(shell_t *ft, char *var_name);
void edit_foreach_var(shell_t *ft, char *var_name, char *data);
int fill_list(list_cmd_foreach_t *list_cmd);
void delete_list_cmd(list_cmd_foreach_t *list_cmd);

/* ---------------------------------------------- */
/* SHELL/INHIBITORS */

/* inhibitors_inside.c */
shell_t *get_ft(shell_t *ft);
char *inhibitor_mask(shell_t *ft, char *str);
int shift_str_left(char *str, int idx, int times);
int inhibitors_inside(shell_t *ft);

/* inhibitors.c */
int remove_inhibitors(char *str);
int count_inhibitors(char *str);
int inhibitors_loop(shell_t *ft, char *s);
int inhibitors(shell_t *ft, char *s);

/* ---------------------------------------------- */
/* SHELL/LINKED_LIST */

/* ll_utils_three.c */
int ll_free_alias(alias_t *head);

/* ll_utils_two.c */
int ll_update_node(shell_t *ft, ll_t **head, char *data, char *new);
int ll_update_node_two(shell_t *ft, char *data, char *new);
int ll_remove_node(ll_t **head, ll_t *node);

/* ll_utils.c */
int add_list(shell_t *ft, char *env);
int env_to_ll(shell_t *ft, char **env);
int ll_free(ll_t *head);
char **ll_to_wordtab(ll_t *head);
char *ll_find(ll_t *head, char *data);

/* ---------------------------------------------- */
/* SHELL/MYSH */

/* cmd_utils.c */
int check_or_and_operators(tree_t *leaf);
int check_parent_redir(shell_t *ft, tree_t *leaf);
char **str_to_tab_with_double_quote(char *str, char **delims, shell_t *ft);
int nb_charac(char *str, char c);

/* cmd.c */
char **create_tab_for_exec(tree_t *leaf, int check, shell_t *ft);
int my_exec(shell_t *ft, tree_t *leaf);
void is_operator(shell_t *ft, tree_t *leaf);
int cmd(shell_t *ft, tree_t *leaf);
int exec_command(shell_t *ft, tree_t *leaf);

/* errors.c */
int check_signals(shell_t *ft, int return_valu);
void check_return_value(char **execve_tab, shell_t *ft);

/* mysh.c */
int forker(shell_t *ft, char *str_access, char **execve_tab, char **env_tab);
char **replace_if_alias(shell_t *ft, char **cmd);
int get_access_and_fork(shell_t *ft, char **cmd);
int is_builtin(char **cmd, shell_t *ft);
int mysh(shell_t *ft);

/* edit_alias.c */
char **edit_tab_alias(char **tab, char **cmd, int index);
char **replace_if_alias(shell_t *ft, char **cmd);
int is_an_alias(shell_t *ft, char *str);
char **check_one_alias(shell_t *ft, char **cmd, char **tab, ll_t **save);

/* prompt.c */
int my_put_rc(int nb);
int display_prompt(shell_t *ft);

/* utils_two.c */
int my_strlen_tab(char **tab);

/* utils.c */
int free_array(char **tab);
int display_array(char **tab);
void *cmdu_free_return(void *ptr, char **tab, void *ret);
char *is_in_path(shell_t *ft, char *cmd);
int print_array(char **tab);

/* ---------------------------------------------- */
/* SHELL/WHICH_WHERE */

/* where.c */
int where_is_builtin(char *str);
int where_is_alias(shell_t *ft, char *str);
int where_is_path(shell_t *ft, char *str);
int my_where(shell_t *ft, char **tab);

/* which.c */
int which_is_builtin(char *str);
int which_is_alias(shell_t *ft, char *str);
int which_is_path(shell_t *ft, char *str);
int my_which(shell_t *ft, char **tab);

/* ---------------------------------------------- */
/* SHELL/VARIABLES */

/* get_env.c */
char *get_env_name(char *data);
char *get_env_data(char *data);

/* replace_var_before_two.c */
char *var_value_next(var_t *var, char *var_name);
char *var_value(shell_t *ft, char *str, int len);
char *find_var_and_replace(shell_t *ft, char *str, int *i, int add);

/* replace_var_before.c */
int verif_chars_var(char *str);
void replace_vars_next(shell_t *ft, char **str, int *i);
void replace_vars(shell_t *ft, char **str);

/* variables_three.c */
int create_variables(shell_t *ft, char **tab);
var_t *find_ll_variables(shell_t *ft, char *var);
int my_set_var(shell_t *ft, char **tab);

/* variables_two.c */
int find_unset_var(shell_t *ft, char *dif);
int my_unset_var(shell_t *ft, char **tab);
int find_same_variables(shell_t *ft, char *var);
char **pars_var(char **tab);
int check_space_var(shell_t *ft, char **tab, char *buff);

/* variables.c */
int var_data_value(shell_t *ft, var_t *new);
int save_variables(shell_t *ft);
char *copy_str(char *buff, int i);
int find_str(shell_t *ft, char *buff);
int ll_delete_variables(var_t **head, var_t *node);

/* ---------------------------------------------- */
/* SHELL/SCRIPTING */

/* read_script */
int scripting(char *file, shell_t *ft);

/* ---------------------------------------------- */
/* main.c */
int init_struct(shell_t *ft);
int epure_parenthesis_tree(tree_t *leaf);
int init_tree(shell_t *ft);
int init_vars(shell_t *ft);

#endif /* !MYSH_H_ */
