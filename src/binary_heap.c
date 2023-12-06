#include "../include/binary_heap.h"
#include "../include/helper.h"
#include "../include/node_graph.h"

heap_t* create_heap(int capacity)
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (node_t**)malloc(capacity * sizeof(node_t*));
    return heap;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left_child(int i)
{
    return 2 * i + 1;
}

int right_child(int i)
{
    return 2 * i + 2;
}

void swap(node_t** x, node_t** y) 
{
    node_t* temp = *x;
    *x = *y;
    *y = temp;
}

node_t* is_in_heap(heap_t* heap, node_t* node)
{
    for (int i = 0; i < heap->size; i++) {
        if (heap->array[i]->x == node->x && heap->array[i]->y == node->y) {
            return heap->array[i];
        }
    }
    return NULL;
}

void insert(heap_t* heap, node_t* item)
{
    // Check if heap is full
    if (heap->size == heap->capacity) { return; }

    // Insert item at the end of the heap
    heap->array[heap->size] = item;
    int i = heap->size;
    heap->size += 1;

    // Move up until heap rule is satisfied
    while (i != 0 && heap->array[parent(i)]->f > heap->array[i]->f) {
        swap(&heap->array[i], &heap->array[parent(i)]);
        i = parent(i);
    }
}

node_t* extract_min(heap_t* heap)
{
    // Check if heap is empty
    if (heap->size == 0) { return NULL; }

    // Check if heap has only one element
    if (heap->size == 1) {
        heap->size -= 1;
        return heap->array[0];
    }

    // Remove minimum value from heap
    node_t* min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size -= 1;

    // Heapify the root
    min_heapify(heap, 0);

    return min;
}

// Heapify the subtree rooted at index i
void min_heapify(heap_t* heap, int i)
{
    int left = left_child(i);
    int right = right_child(i);
    int smallest = i;

    // Check if left/right child exists and is smaller than root
    if (left < heap->size && heap->array[left]->f < heap->array[i]->f) {
        smallest = left;
    }
    if (right < heap->size && heap->array[right]->f < heap->array[smallest]->f) {
        smallest = right;
    }

    // Recursively heapify until root is smaller than both children
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        min_heapify(heap, smallest);
    }
}
