#include "header.h"
#include "cli.h"

/* Structs */
#ifndef _MAP_NODE_
#define _MAP_NODE_
typedef struct node_s {
    char type;          // type of node
    int vertex;         // vertex number
    int x;              // x-position
    int y;              // y-position
    int g;              // cost from start
    int h;              // manhattan distance
    int f;              // total cost
    struct node_s* successor;       // parent node
    struct node_s* neighbors[4];    // [top, left, right, bottom]
} node_t;
#endif

#ifndef _NODE_ARRAY_
#define _NODE_ARRAY_
typedef struct {
    int size;
    node_t** array;
} n_array_t;
#endif

/* Function Prototypes */
node_t* create_node(legend_t* map, s_array_t* map_rows, node_t* q, int x, int y);
node_t* create_type_node(legend_t* map, s_array_t* map_rows, char c);
n_array_t* create_node_array(int size);
void add_node_to_array(n_array_t* node_array, node_t* node);
void add_neighbors(legend_t* legend, s_array_t* data, node_t* src);
node_t* is_end_node(legend_t* legend, node_t* node);
node_t* is_in_array(node_t** closed_list, node_t* node);
int manhattan_distance(int x, int y, node_t* end);  