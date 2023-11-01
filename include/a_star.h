#include "header.h"
#include "cli.h"
#include "node_graph.h"
#include "binary_heap.h"

/* Function Prototypes */
bool a_star(legend_t** legend, s_array_t** data); 
node_t* a_loop(heap_t* o, n_array_t* c, legend_t** l, s_array_t** d); 
node_t* n_loop(heap_t* open, n_array_t* closed, legend_t** l, node_t* node);
void end_found(n_array_t* closed_list, node_t* node, int index);
void trace_path(heap_t* o, n_array_t* c,legend_t* l, s_array_t* d, node_t* p);
void print_map(legend_t* legend, s_array_t* data);
