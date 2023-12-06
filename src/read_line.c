#include "../include/read_line.h"
#include "../include/helper.h"

char *my_read_line(int fd, read_line_t **buf) 
{
    int total_bytes = 0;
    int bytes = 1;
    if (*buf != NULL) {
        if (!(handle_leftover(buf, &total_bytes))) { return (*buf)->storage; }
    } else { 
        if (!init_read_line(buf)) { return NULL; } 
    }

    switch (read_line_loop(buf, fd, &bytes, &total_bytes)) {
        case 0:
            return NULL;
        case 1:
            break;
        case 2:
            return (*buf)->storage;
    }

    if (bytes == 0 && total_bytes == 0) {
        flush_read_line(buf);
        return NULL;
    }

    (*buf)->leftover = NULL;
    return (*buf)->storage;
}


bool handle_leftover(read_line_t** buf, int* total_bytes)
{
    if ((*buf)->leftover != NULL) {
        *total_bytes = my_strlen((*buf)->leftover);
        int index = 0;

        if (!(index = find_newline((*buf)->leftover))) {
            // If no '\n' found, allocate memory for buf->storage
            (*buf)->storage = (char*)malloc(sizeof(char) * 
                (*total_bytes + READLINE_READ_SIZE + 1));
            my_strcpy((*buf)->storage, (*buf)->leftover);
            free((*buf)->leftover);
            (*buf)->leftover = NULL;
        } else {
            // If '\n' found, copy first line into buf->storage
            copy_first_line(buf, (*buf)->leftover, *total_bytes);
            return false;    
        }
    } 
    else { (*buf)->storage = (char*)malloc(sizeof(char) * (READLINE_READ_SIZE + 1)); }

    return true;
}

int read_line_loop(read_line_t** buf, int fd, int* bytes, int* total_bytes) 
{
    while (*bytes > 0) {
        *bytes = read(fd, (*buf)->storage + *total_bytes, READLINE_READ_SIZE);
        *total_bytes += *bytes;

        if (*bytes == -1) { return 0; }
        if (*bytes == 0) { return 1; }

        (*buf)->storage[*total_bytes] = '\0';
        if ((*buf)->storage[*total_bytes - 1] == '\n') {
            (*buf)->storage[*total_bytes - 1] = '\0';
        }

        // Check for echo edge case
        int echo_toggle = is_echo((*buf)->storage, *bytes);
        if (echo_toggle) {
            if ((*buf)->storage[*total_bytes - 1] == '\n') {
                (*buf)->storage[*total_bytes - 1] = '\0';
            }
            convert_newline_char((*buf)->storage, *bytes);
        }
        // Copy first line only into buf->storage + return
        copy_first_line(buf, (*buf)->storage, *total_bytes);
        return 2;
    }

    return 1;
}

void copy_first_line(read_line_t** buf, char* src, int src_len)
{
    int index = 0;
    if (!(index = find_newline(src))) { return; }
    if (index == src_len) {
        (*buf)->storage = init_string(src_len);
        my_strcpy((*buf)->storage, src);
        free((*buf)->leftover);
        (*buf)->leftover = NULL;
        return;
    }

    // Store next line in temp_buf_1, leftover in temp_buf_2
    char *temp_buf_1 = init_string(index + 1);
    char *temp_buf_2 = init_string(src_len - index + 1);
    my_strncpy(temp_buf_1, src, index);
    my_strcpy(temp_buf_2, src + index);
    free(src);

    // Copy temp buffers into readline_t
    (*buf)->storage = malloc(sizeof(char) * my_strlen(temp_buf_1) + 1);
    my_strcpy((*buf)->storage, temp_buf_1);
    (*buf)->leftover = malloc(sizeof(char) * my_strlen(temp_buf_2) + 1);
    my_strcpy((*buf)->leftover, temp_buf_2);

    free(temp_buf_1);
    free(temp_buf_2);
}


int is_echo(char* string, int bytes) 
{
    for (int i = 0; i < bytes - 1; i++) {
        if (string[i] == '\\' && string[i + 1] == 'n') {
            return 1;
        } 
    } 

    return 0;
}

int convert_newline_char(char* string, int bytes) 
{
    int j = 0;
    int k = 0;

    for (int i = 0; i < bytes - 1; i++) {
        if (string[i] == '\\' && string[i + 1] == 'n') {
            string[i] = '\n';
            j = i + 1;
            while (j < bytes - 1) {
                string[j] = string[j + 1];
                j += 1;
            }
            k = i;
        } 
    } 

    return k;
}

int find_newline(char* string) 
{
    int index = my_strchr_index(string, '\n');
    return index;
}

// Flush buffer
void flush_read_line(read_line_t **buf)
{
    free((*buf)->storage);
    free(*buf);
    *buf = NULL;
}

bool init_read_line(read_line_t** buf) 
{
    *buf = (read_line_t*)malloc(sizeof(read_line_t) + 1);
    (*buf)->storage = (char*)malloc(sizeof(char) * (READLINE_READ_SIZE + 1));

    if ((*buf)->storage == NULL) {
        return false;
    }

    return true;
}

char* init_string(int len) 
{
    char* string = (char*)malloc(sizeof(char) * (len + 1));
    memset(string, 0, len + 1); // use init_string instead?

    return string;
}

