#include "header.h"
#include "cli.h"

/* function prototypes */
bool data_error(legend_t* legend, s_array_t* data);
bool map_size_error(legend_t* legend);
bool col_consistency_error(legend_t* legend, s_array_t* data);
bool valid_char_error(legend_t* legend, s_array_t* data);
bool string_array_error(s_array_t* tokens);
bool row_count_error(s_array_t* data, int num_rows);
bool arg_count_error(int argc);
void parse_error(void);
void map_error(void);
