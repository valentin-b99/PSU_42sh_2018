/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** backsticks
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int error_backsticks(char *cmd)
{
    int i = -1;
    int count = 0;

    while (cmd[++i])
        if (cmd[i] == '`')
            ++count;
    if (count % 2) {
        printf("Unmatched '`'.\n");
        free(cmd);
        cmd = NULL;
        return (1);
    }
    return (count ? 0 : 1);
}

char *create_ret(char *cmd, int pos, int i, char *output)
{
    char *ret = malloc(sizeof(char) * (my_strlen(cmd) + 1));

    if (ret == NULL)
        return (NULL);
    cmd[pos] = 0;
    my_strcpy(ret, cmd);
    ret = newcat(ret, output);
    ret = newcat(ret, cmd + i + 1);
    free(cmd);
    return (ret);
}

void backsticks(shell_t *ft, char **c)
{
    char *cmd = *c;
    int pos = 0;
    int i = -1;
    char *output = NULL;
    char exec[my_strlen(cmd)];

    if (!*c || error_backsticks(cmd))
        return;
    while (cmd[++i] != '`');
    pos = i;
    while (cmd[++i] != '`')
        exec[i - pos - 1] = cmd[i];
    exec[i - pos - 1] = 0;
    if (!(output = exec_backsticks(ft, exec)))
        return;
    *c = create_ret(cmd, pos, i, output);
    backsticks(ft, c);
}