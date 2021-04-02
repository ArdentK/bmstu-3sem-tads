#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"

//Узел дерева
typedef struct node tree_node_t;

struct node
{
    long data;          // Число, содержадееся в узле
    tree_node_t *left;  // Ссылка на левый нижний узел
    tree_node_t *right; // Ссылка на правый нижний узел
};

// Инициализация дерева
tree_node_t *init_tree(FILE *f);
// Освобождение дерева
void tree_free(tree_node_t *tree);

// Поиск элемента в графе
tree_node_t *find(tree_node_t *head, long elem);

tree_node_t *insert(tree_node_t *head, tree_node_t *elem);

void export_dot_tree(FILE *f, tree_node_t *head);

//Инициализачия АВЛ-дерева
tree_node_t *init_balance_tree(FILE *f);
// Вставка в АВЛ-дерево
tree_node_t *insert_in_avl(tree_node_t *head, tree_node_t *elem);
//Балансировка АВЛ-дерева
tree_node_t *balance(tree_node_t *node);
int cmp_balance(tree_node_t *node);
tree_node_t *rotate_left(tree_node_t *node);
tree_node_t *rotate_right(tree_node_t *node);
size_t get_height(tree_node_t *head);
//Удаление из АВЛ-дерева
tree_node_t *del_in_avl(tree_node_t *head, long elem);
tree_node_t *del(tree_node_t *head, long elem);

#endif //TREE_H