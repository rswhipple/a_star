#include "../include/cli.h"
#include "../include/binary_heap.h"
#include "../include/node_graph.h"

s_array_t* init_string_array(int size) 
{
    s_array_t* new_array = malloc(sizeof(s_array_t));
    new_array->array = malloc(sizeof(char*) * size);
    new_array->size = 0;

    for (int i = 0; i < size; i++) { new_array->array[i] = NULL; }

    return new_array;
}

void free_string_array(s_array_t* param_1)
{ 
    int i = 0;
    while (i < param_1->size) {
        free(param_1->array[i]);
        i++;
    }
    
    free(param_1->array);
    free(param_1);
}

void free_heap(heap_t* heap)
{
    while (heap->size) {
        free(heap->array[heap->size - 1]);
        heap->size -= 1;
    }

    free(heap->array);
    free(heap);
}

void free_node_array(n_array_t* node_array)
{
    int i = 0;

    while (i < node_array->size) {
        if (node_array->array[i]) {
            free(node_array->array[i]);
        }
        i++;
    }

    free(node_array->array);
    free(node_array);
}
