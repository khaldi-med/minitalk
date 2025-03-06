# Makefile for minitalk project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
PRINTF_DIR = ./printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

# Source files
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Object files
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Executable names
SERVER = server
CLIENT = client

# Default target
all: $(PRINTF_LIB) $(SERVER) $(CLIENT)

# Compile printf library
$(PRINTF_LIB):
	@make -C $(PRINTF_DIR)

# Compile server
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(PRINTF_LIB)

# Compile client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(PRINTF_LIB)

# Compile .c files to .o files
%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@make -C $(PRINTF_DIR) clean
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

# Clean object files and executables
fclean: clean
	@make -C $(PRINTF_DIR) fclean
	rm -f $(SERVER) $(CLIENT)

# Clean and recompile
re: fclean all

# Ensure these targets are not matched with files
.PHONY: all clean fclean re

