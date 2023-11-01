#include <stdlib.h>
#include "../include/helper.h"
#include "../include/cli.h"
#include "../include/a_star.h"
#include "../include/error_handler.h"
int main(int argc, char** argv) 
{

    int success = my_mouse(argc, argv);
    if (success == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int my_mouse(int argc, char** argv) 
{
    legend_t* legend = NULL;
    s_array_t* data = NULL;

    // Parse user input
    if (!(data = parse_user_input(argc, argv, &legend))) { return EXIT_FAILURE; }
    
    // Run A* algorithm + print map
    if (!(a_star(&legend, &data))) { return EXIT_FAILURE; }

    return EXIT_SUCCESS;
}
