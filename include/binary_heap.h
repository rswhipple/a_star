#include "header.h"
#include "node_graph.h"

/* structs */

#ifndef _HEAP_
#define _HEAP_
typedef struct {
    int size;
    int capacity;
    node_t** array;
} heap_t;
#endif

/* function prototypes */

heap_t* create_heap(int capacity);
int parent(int i);
int left_child(int i);
int right_child(int i);
void swap(node_t** x, node_t** y);
node_t* is_in_heap(heap_t* heap, node_t* node);
void insert(heap_t* heap, node_t* item);
node_t* extract_min(heap_t* heap);
void min_heapify(heap_t* heap, int i);
