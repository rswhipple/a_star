#include "../include/cli.h"
#include "../include/read_line.h"
#include "../include/helper.h"
#include "../include/error_handler.h"
#include "../include/memory.h"

s_array_t* parse_user_input(int argc, char** argv, legend_t** legend)
{
    int fd;
    if (arg_count_error(argc)) { return NULL; }
    if (!open_map(&fd, argv[1])) { return NULL; }

    read_line_t *buf = NULL;
    char* first_line = NULL;
    if (!(*legend = parse_first_line(fd, &buf, &first_line))) { return NULL; }

    s_array_t* data = NULL;
    if (!(data = read_map(fd, (*legend)->num_rows, &buf, first_line))) 
            { return NULL; }

    if ((data_error(*legend, data))) { return NULL; }

    return data;
}

legend_t* parse_first_line(int fd, read_line_t **buf, char** first_line) 
{
    if (!(*first_line = my_read_line(fd, buf))) {
        map_error();
        return NULL;
    }

    s_array_t* tokens = NULL;
    if(!(tokens = create_tokens(*first_line))) {
        map_error();
        return NULL;
    }

    if (string_array_error(tokens)) { return NULL; }

    legend_t* legend = create_legend(tokens->array);
    free_string_array(tokens);

    return legend;
}

s_array_t* read_map(int fd, int num_rows, read_line_t **buf, char* first_line) 
{
    char* str = NULL;
    s_array_t* data = init_string_array(num_rows + 2);
    data->array[0] = first_line;
    data->size += 1;
    
    while ((str = my_read_line(fd, buf)) != NULL)
    {
        if (str[0] == '\0' || str[0] == '\n') {
            free(str);
            break;
        }
        data->array[data->size] = str;
        data->size += 1;
    }

    return data;
}

s_array_t* create_tokens(char* first_line) 
{
    s_array_t* tokens = init_string_array(MAX_TOKENS);
    int i = 0, j = 0;

    while (first_line[i] != '\0' && j < MAX_TOKENS) {
        if (is_number(first_line[i])) {
            tokens->array[j] = copy_numbers_to_string(tokens->array[j], first_line, &i);
            tokens->size += 1;
            j += 1;
        }  else {
            tokens->array[j] = malloc(sizeof(char) * 2);
            tokens->array[j][0] = first_line[i++];
            tokens->array[j][1] = '\0';
            tokens->size += 1;
            j += 1;
        } 
    }                  
    if (j != 7) { return NULL; } 

    return tokens; 
}

char* copy_numbers_to_string(char* dst, char* src, int* i) 
{
    int j = 0, k = 0;
    int placeholder = *i;

    while (is_number(src[*i])) {
        j += 1;
        *i += 1;
    }

    // Initialize dst
    dst = malloc(sizeof(char) * (j + 1));
    for (k = 0; k < j + 1; k++) { dst[k] = 0; }

    for (k = 0; k < j; k++) {
        dst[k] = src[placeholder];
        placeholder += 1;
    }

    dst[j] = '\0';

    return dst;
}

legend_t* create_legend(char** tokens) 
{
    legend_t* map = malloc(sizeof(legend_t));
    map->num_rows = my_atoi(tokens[0]);
    map->num_cols = my_atoi(tokens[2]);
    map->wall = tokens[3][0];
    map->empty = tokens[4][0];
    map->path = tokens[5][0];
    map->start = tokens[6][0];
    map->end = tokens[6][1];
    map->end_node = NULL;
    return map;
}

bool open_map(int* fd, char* filename) 
{
    *fd = get_fd(filename);

    if (*fd == -1) {
        map_error();
        return false;
    }
    return true;
}

int get_fd(char* filename) 
{
    int fd = open(filename, O_RDONLY);
    return fd;
}
