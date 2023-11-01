#include "../include/node_graph.h"
#include "../include/cli.h"

node_t* create_node(legend_t* legend, s_array_t* data, node_t* q, int x, int y)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->type = data->array[x][y];
    if (x == 1) { new_node->vertex = y; }
    else { new_node->vertex = (x - 1) * legend->num_cols + y; }
    new_node->x = x;
    new_node->y = y;
                           
    if (q == NULL) { new_node->g = 0; } 
    else { new_node->g = q->g + 1; }

    if (legend->end_node == NULL) { new_node->h = 0; } 
    else { new_node->h = manhattan_distance(x, y, legend->end_node); }

    new_node->f = new_node->g + new_node->h;
    new_node->successor = q;
    for (int i = 0; i < 4; i++) { new_node->neighbors[i] = NULL; }

    return new_node;
}

node_t* create_type_node(legend_t* legend, s_array_t* data, char type) 
{
    // Skip first line of map
    int i = 1;
    while (i < legend->num_rows + 1) {
        int j = 0;
        while (j < legend->num_cols) {
            if (data->array[i][j] == type) {
                node_t* node = create_node(legend, data, NULL, i, j);
                return node;
            } 
            j += 1;
        }
        i += 1;
    }
    return NULL;
}

n_array_t* create_node_array(int size) 
{
    n_array_t* node_array = (n_array_t*)malloc(sizeof(n_array_t));
    node_array->size = size;
    node_array->array = (node_t**)malloc(sizeof(node_t*) * size);

    for (int i = 0; i < size; i++) { 
        node_array->array[i] = NULL; 
    }

    return node_array;
}

void add_node_to_array(n_array_t* node_array, node_t* node) 
{
    node_array->array[node->vertex] = node;
}

void add_neighbors(legend_t* legend, s_array_t* data, node_t* src) 
{
    // Add up neighbor
    if (src->x > 1 && data->array[src->x - 1][src->y] != legend->wall) {
        src->neighbors[0] = create_node(legend, data, src, src->x - 1, src->y);
    }

    // Add left neighbor
    if (src->y > 0 && data->array[src->x][src->y - 1] != legend->wall) {
        src->neighbors[1] = create_node(legend, data, src, src->x, src->y - 1);
    }

    // Add right neighbor
    if (src->y < legend->num_cols - 1 && data->array[src->x][src->y + 1] != legend->wall) {
        src->neighbors[2] = create_node(legend, data, src, src->x, src->y + 1);
    }

    // Add down neighbor
    if (src->x < legend->num_rows && data->array[src->x + 1][src->y] != legend->wall) {
        src->neighbors[3] = create_node(legend, data, src, src->x + 1, src->y);
    }
}

node_t* is_end_node(legend_t* legend, node_t* node)
{
    if (node == NULL) { return NULL; }

    if (node->type == legend->end) {
        return node;
    }

    return NULL;
}

node_t* is_in_array(node_t** closed_list, node_t* node) 
{
    if (closed_list[node->vertex] != NULL) {
        return closed_list[node->vertex];
    }
    return NULL;
}

int manhattan_distance(int x1, int y1, node_t* end) 
{
    int x2 = end->x;
    int y2 = end->y;
    return abs(x1 - x2) + abs(y1 - y2);
}
