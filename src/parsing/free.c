/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int rint_free(void *ptr)
{
    ptr ? free(ptr) : 0;
    return (0);
}

int free_tree(tree_t *tree)
{
    if (!tree)
        return (0);
    if (tree->left)
        free_tree(tree->left);
    if (tree->right)
        free_tree(tree->right);
    if (tree->name)
        free(tree->name);
    if (tree->hidden)
        free(tree->hidden);
    if (tree)
        free(tree);
    return (0);
}
