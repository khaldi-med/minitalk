NAME = client server
BONUS = client_bonus server_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

bonus: $(BONUS)

$(PRINTF):
	@make -C $(PRINTF_DIR)

client: client.c $(PRINTF)
	$(CC) $(CFLAGS) $< $(PRINTF) -o $@

server: server.c $(PRINTF)
	$(CC) $(CFLAGS) $< $(PRINTF) -o $@

client_bonus: client_bonus.c $(PRINTF)
	$(CC) $(CFLAGS) $< $(PRINTF) -o $@

server_bonus: server_bonus.c $(PRINTF)
	$(CC) $(CFLAGS) $< $(PRINTF) -o $@

clean:
	@make -C $(PRINTF_DIR) clean
	@rm -f client server client_bonus server_bonus *.o

fclean: clean
	@make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
