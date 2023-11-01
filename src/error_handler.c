#include "../include/error_handler.h"
#include "../include/helper.h"
bool data_error(legend_t* legend, s_array_t* data)  
{
    // Check if number of rows is correct
    if (row_count_error(data, legend->num_rows)) { return true; }

    // Check if map is empty
    if (map_size_error(legend)) { return true; }

    // Check if all rows have the correct number of columns
    if (col_consistency_error(legend, data)) { return true; }

    // Check if all characters are valid + make sure 'start', 'end' are present
    if (valid_char_error(legend, data)) { return true; }

    return false;
}

bool row_count_error(s_array_t* data, int num_rows) 
{
    if (data->size != num_rows + 1) {
        map_error();
        return true;
    }

    return false;
}

bool map_size_error(legend_t* legend) 
{
    if (legend->num_rows < 3 || legend->num_cols < 3 || 
            legend->start == legend->end || legend->empty == legend->wall ||
            legend->path == legend->wall) {
        map_error();
        return true;
    }

    return false;
}

bool col_consistency_error(legend_t* legend, s_array_t* data) 
{
    int expected_cols = legend->num_cols;

    for (int i = 1; i < legend->num_rows; i++) {
        if (my_strlen(data->array[i]) != expected_cols) {
            map_error();
            return true;
        }
    }

    return false;
}

bool valid_char_error(legend_t* legend, s_array_t* data) 
{
    int found_start = 0;
    int found_end = 0;
    // Check for invalid characters in the map
    for (int i = 1; i < data->size; i++) {
        for (int j = 0; j < legend->num_cols; j++) {
            char cell = data->array[i][j];
            if (cell == legend->start) { found_start += 1; }
            if (cell == legend->end) { found_end += 1; }
            if (cell != legend->empty && cell != legend->wall && !is_number(cell)) {
                map_error();
                return true;
            }
        }
    }

    if (found_start != 1 || found_end != 1) {
        map_error();
        return true;
    }

    return false;
}

bool string_array_error(s_array_t* tokens) 
{
    if (!is_number(tokens->array[0][0]) || !is_number(tokens->array[2][0])) {
        map_error();
        return true;
    }

    return false;

}

bool arg_count_error(int argc) 
{
    if (argc != 2) {
        map_error();
        return true;
    }
    return false;
}

void map_error(void) 
{
    char* error = "MAP ERROR";
    write(2, error, my_strlen(error)); 
}
