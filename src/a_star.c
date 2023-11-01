#include "../include/a_star.h"
#include "../include/cli.h"
#include "../include/node_graph.h"
#include "../include/binary_heap.h"
#include "../include/helper.h"
#include "../include/memory.h"


bool a_star(legend_t** l, s_array_t** data)
{ 
    // Create start + end nodes
    node_t* end = create_special_node(*l, *data, (*l)->end);
    (*l)->end_node = end;
    node_t* start = create_special_node(*l, *data, (*l)->start);
    node_t* temp = NULL;

    // Create open + closed lists, insert start node into open list
    int size = (*l)->num_rows * (*l)->num_cols;
    // printf("Number of cells: %i\n", size);
    heap_t* open_list = create_heap(size);
    n_array_t* closed_list = create_node_array(size);
    insert(open_list, start);

    // Run A* loop
    temp = a_loop(open_list, closed_list, l, data);

    // Print map with reconstructed path
    trace_path(open_list, closed_list, *l, *data, temp);

    return EXIT_SUCCESS;
}

node_t* a_loop(heap_t* open, n_array_t* closed, legend_t** l, s_array_t** data)
{
    node_t* temp = NULL;

    while (open->size > 0) {
        node_t* current = extract_min(open); 
        add_neighbors(*l, *data, current);

        for (int i = 0; i < 4; i++) {
            if ((temp = is_end_node(*l, current->neighbors[i]))) { return temp; }
            if (current->neighbors[i] == NULL) { continue; }
            if ((temp = is_in_heap(open, current->neighbors[i])) && 
                    current->neighbors[i]->f >= temp->f) { 
                free(current->neighbors[i]);
                continue; 
            }
            if ((temp = is_in_closed_list(closed->array, current->neighbors[i])) && 
                    current->neighbors[i]->f >= temp->f) { 
                free(current->neighbors[i]);
                continue; 
            }
            insert(open, current->neighbors[i]);
        }

        add_node_to_array(closed, current);
    }
    return NULL;
}



void trace_path(heap_t* o, n_array_t* c,legend_t* l, s_array_t* d, node_t* p) 
{
    // Create path from end back to start
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
    free(p);
    free(l);
}

void print_map(legend_t* legend, s_array_t* data) 
{
    int i;

    for (i = 0; i < legend->num_rows; i++) {
        printf("%s\n", data->array[i]);
    }
    printf("%s", data->array[i]);
}
