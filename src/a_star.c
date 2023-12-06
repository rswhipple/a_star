#include "../include/a_star.h"
#include "../include/cli.h"
#include "../include/node_graph.h"
#include "../include/binary_heap.h"
#include "../include/helper.h"
#include "../include/memory.h"

bool a_star(legend_t** l, s_array_t** data)
{ 
    // Create start and end nodes
    node_t* end = create_type_node(*l, *data, (*l)->end); 
    (*l)->end_node = end;
    node_t* start = create_type_node(*l, *data, (*l)->start);
    node_t* temp = NULL;

    // Create open and closed lists
    int size = (*l)->num_rows * (*l)->num_cols;
    heap_t* open_list = create_heap(size);
    n_array_t* closed_list = create_node_array(size);

    // Run A* loop
    insert(open_list, start);
    temp = a_loop(open_list, closed_list, l, data);
    free(end);

    // Print map with reconstructed path
    trace_path(open_list, closed_list, *l, *data, temp);
    free(temp);

    return EXIT_SUCCESS;
}

node_t* a_loop(heap_t* open, n_array_t* closed, legend_t** l, s_array_t** data)
{
    node_t* temp = NULL;

    while (open->size > 0) {
        node_t* current = extract_min(open); 
        add_neighbors(*l, *data, current);

        if ((temp = n_loop(open, closed, l, current))) { return temp; } 

        add_node_to_array(closed, current);
    }

    return NULL;
}

node_t* n_loop(heap_t* open, n_array_t* closed, legend_t** l, node_t* node)
{
    node_t* temp = NULL;

    // Cycle through neighbors, remove node if better path exists or add to open list
    for (int i = 0; i < 4; i++) {
        if (node->neighbors[i] == NULL) { continue; }
        if ((temp = is_end_node(*l, node->neighbors[i]))) { 
            // Handle memory when end node is reached
            end_found(closed, node, i);
            return temp; 
        }
        if ((temp = is_in_heap(open, node->neighbors[i])) && 
                node->neighbors[i]->f >= temp->f) { 
            free(node->neighbors[i]);
            continue; 
        }
        if ((temp = is_in_array(closed->array, node->neighbors[i])) && 
                node->neighbors[i]->f >= temp->f) { 
            free(node->neighbors[i]);
            continue; 
        }
        insert(open, node->neighbors[i]);
    }

    return NULL;
}

void end_found(n_array_t* closed_list, node_t* node, int index) 
{
    int i = index + 1;
    
    while (i < 4) {
        free(node->neighbors[i]);
        i++;
    }
    
    add_node_to_array(closed_list, node);
}

void trace_path(heap_t* o, n_array_t* c,legend_t* l, s_array_t* d, node_t* p) 
{
    // Create path from end to start
    int steps = 0;
    node_t* current = p->successor;
    while (current->successor != NULL) {
        d->array[current->x][current->y] = l->path;
        current = current->successor; 
        steps += 1;
    }

    // Print map
    print_map(l, d);
    printf("%d STEPS!\n", steps); 

    // Free memory
    free_heap(o);
    free_node_array(c);
    free_string_array(d);
    free(l);
}

void print_map(legend_t* legend, s_array_t* data) 
{
    int i;

    for (i = 0; i <= legend->num_rows; i++) {
        printf("%s\n", data->array[i]);
    }
}
