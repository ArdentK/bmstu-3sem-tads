#define __USE_MINGW_ANSI_STDIO 1

#include "graph_matrix_func.h"

matrix_t *allocate_matrix(size_t rows, size_t cols)
{
    matrix_t *mtx = malloc(sizeof(matrix_t));

    mtx->cols = cols;
    mtx->rows = rows;

    mtx->data = calloc(sizeof(int *) * rows + sizeof(int) * rows * cols, 1);

    for (size_t i = 0; i < rows; i++)
        mtx->data[i] = (int *)(mtx->data + rows) + cols * i;

    return mtx;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->data);
    free(matrix);
}

graph_t *create_graph_from_file(FILE *file)
{
    int err = EXIT_SUCCESS;

    graph_t *graph = calloc(sizeof(*graph), 1);

    if (fscanf(file, "%zu", &graph->num) != 1 || graph->num == 0)
    {
        free_graph(graph);
        return NULL;
    }

    graph->adjacency_matrix = allocate_matrix(graph->num, graph->num);

    size_t from, to;
    while (!err)
    {
        int rc = fscanf(file, "%zu->%zu", &from, &to);
        if (rc != 2)
        {
            if (rc < 0)
                break;
            else
            {
                free_graph(graph);
                err = INPUT_ERROR;
                return NULL;
            }
        }

        if (from < 1 || to < 1 || from > graph->num || to > graph->num)
        {
            err = INPUT_ERROR;
            free_graph(graph);
            return NULL;
        }

        graph->adjacency_matrix->data[from - 1][to - 1] = 1;
    }

    create_reachability_matrix(graph);

    return graph;
}

matrix_t *copy_matrix(matrix_t *src)
{
    matrix_t *dst = allocate_matrix(src->rows, src->cols);

    for (size_t i = 0; i < src->rows; i++)
        for (size_t j = 0; j < src->cols; j++)
            dst->data[i][j] = src->data[i][j];

    return dst;
}

void create_reachability_matrix(graph_t *graph)
{
    matrix_t *result = copy_matrix(graph->adjacency_matrix);
    matrix_t *buf = copy_matrix(graph->adjacency_matrix);

    for (size_t i = 0; i < graph->num - 1; i++)
    {
        matrix_t *cur = multiplication(buf, graph->adjacency_matrix);
        free_matrix(buf);
        buf = cur;

        matrix_t *result_sum = addition(result, buf);
        free_matrix(result);
        result = result_sum;
    }

    graph->reachability = result;
}

void free_graph(graph_t *graph)
{
    free_matrix(graph->adjacency_matrix);
    free_matrix(graph->reachability);

    free(graph);
}

matrix_t *addition(matrix_t *mtx_1, matrix_t *mtx_2)
{
    if (!mtx_1 || !mtx_2)
        return NULL;

    if (mtx_1->rows != mtx_2->rows || mtx_1->cols != mtx_2->cols)
        return NULL;

    matrix_t *new_mtx = allocate_matrix(mtx_1->rows, mtx_1->cols);

    if (!new_mtx)
        return NULL;

    for (size_t j = 0; j < mtx_1->rows; j++)
        for (size_t i = 0; i < mtx_1->cols; i++)
            new_mtx->data[j][i] = mtx_1->data[j][i] + mtx_2->data[j][i];

    return new_mtx;
}

matrix_t *multiplication(matrix_t *mtx_1, matrix_t *mtx_2)
{
    if (!mtx_1 || !mtx_2)
        return NULL;
    if (mtx_1->cols != mtx_2->rows)
        return NULL;

    matrix_t *new_mtx = allocate_matrix(mtx_1->rows, mtx_2->cols);

    if (new_mtx == NULL)
        return NULL;

    for (size_t i = 0; i < mtx_1->rows; i++)
        for (size_t k = 0; k < mtx_2->rows; k++)
            for (size_t j = 0; j < mtx_2->cols; j++)
                new_mtx->data[i][j] += mtx_1->data[i][k] * mtx_2->data[k][j];

    return new_mtx;
}

void find_points(graph_t graph, size_t point)
{
    int num = 0;

    printf("Из вершины %zu НЕ достижимы вершины:\n", point + 1);

    for (size_t i = 0; i < graph.num; i++)
        if (!graph.reachability->data[point][i] && i != point)
        {
            printf("- %zu\n", i + 1);
            num += 1;
        }

    if (!num)
        printf("\nНедостижимых вершин в графе нет\n");
}

void export_dot_reachability(FILE *f, graph_t *graph, size_t point)
{
    fprintf(f, "digraph graphname {\n");

    for (size_t i = 0; i < graph->num; i++)
        if (i == point)
            fprintf(f, "\"%zu\" [color=blue];\n", i + 1);
        else if (graph->reachability->data[point][i])
            fprintf(f, "\"%zu\" [color=black];\n", i + 1);
        else
            fprintf(f, "\"%zu\" [color=red];\n", i + 1);

    for (size_t i = 0; i < graph->num; i++)
        for (size_t j = 0; j < graph->num; j++)
            if (graph->adjacency_matrix->data[i][j])
                fprintf(f, "\"%zu\" -> \"%zu\";\n", i + 1, j + 1);

    fprintf(f, "}");
}
