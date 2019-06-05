/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

tree_t *root_tree(char *root)
{
    tree_t *tr = malloc(sizeof(*tr));

    if (!tr)
        return (NULL);
    tr->name = my_strdup(root);
    tr->left = NULL;
    tr->right = NULL;
    tr->parent = NULL;
    tr->hidden = NULL;
    return (tr);
}

int add_leaf(tree_t *leaf, char *left, char *right, char *root)
{
    tree_t *node = malloc(sizeof(tree_t));
    shell_t *tmp = get_ft(NULL);

    if (!node)
        return (84);
    if (leaf->name) {
        free(leaf->name);
        if ((leaf->name = check_glob(root)) == NULL)
            return (84);
    }
    node->return_val = -1;
    node->check = 0;
    node->if_each_check = 0;
    node->left = NULL;
    node->right = NULL;
    node->if_each_check = tmp->if_check ? 1 : 0;
    node->hidden = inhibitor_mask(get_ft(NULL), left ? left : right);
    node->parent = leaf;
    if ((node->name = check_glob(left ? left : right)) == NULL)
        return (84);
    left ? leaf->left = node : 0;
    !left && right ? leaf->right = node : 0;
    return (left && right ? add_leaf(leaf, NULL, right, root) : 0);
}

int print_tree_prefix(tree_t *tr)
{
    if (!tr)
        return (84);
    if (tr->parent != NULL)
        my_printf("(%s) -> (%s)\n", tr->parent->name, tr->name);
    else
        my_printf("(%s)\n", tr->name);
    if (tr->left != NULL) {
        print_tree_prefix(tr->left);
    }
    if (tr->right != NULL)
        print_tree_prefix(tr->right);
    return (0);
}
