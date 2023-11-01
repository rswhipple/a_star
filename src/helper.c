#include "../include/helper.h"
#include "../include/cli.h"

bool is_number(char c)
{
    if (c >= '0' && c <= '9') {
        return true; 
    } else {
        return false;
    }
}

char* my_realloc_str(char* ptr, size_t size) 
{
    char *buf = (char*)malloc(sizeof(char) * size);
    buf = my_strcpy(buf, ptr);
    free(ptr);

    return buf;
}

char* my_strchr(char* str_1, char char_1)
{
    int i;

    for (i = 0; i <= my_strlen(str_1); i++) {
        if (str_1[i] == char_1) {
            return &str_1[i];
        }
    }

    return "";
}

int my_strchr_index(char* str_1, char char_1)
{
    int i;

    for (i = 0; i <= my_strlen(str_1); i++) {
        if (str_1[i] == char_1) {
            return i + 1;
        }
    }

    return 0;
}

char* my_strcpy(char* dst, char* src)
{
    int i;
    int length = my_strlen(src);

    for (i = 0; i < length; i++) {
        dst[i] = src[i]; 
    }

    dst[i] = '\0';

    return dst;
}

char* my_strncpy(char* dst, char* src, int n)
{
    char* original_dst = dst;
    int i;

    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }

    *--dst = '\0';

    return original_dst;
}

int my_strlen(char* str) 
{
    int i = 0;

    do {
        i += 1;
    } while (str[i] != '\0');

    return i;
}

int my_atoi(char* param_1) // no negative
{
    int output = 0;
    int i = 0;

    while (i < my_strlen(param_1)) {
        output *= 10;
        output += param_1[i] - '0';
        i++;
    }

    return output;
}

