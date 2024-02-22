TARGET = my_mouse
SRCS = src/my_mouse.c src/cli.c src/a_star.c src/node_graph.c src/read_line.c src/helper.c src/binary_heap.c src/error_handler.c src/memory.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address --pedantic-errors
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(TARGET)

re: fclean all
