#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/* structs */
#ifndef _LEGEND_
#define _LEGEND_
typedef struct {
    int num_rows;
    int num_cols;
    char wall;
    char empty;
    char path;
    char start;
    char end;
    void* end_node;
} legend_t;
#endif

/* function prototypes */
int my_mouse(int argc, char** argv);
