CC = cc
CFLAGS = -Wall -Wextra -Werror
SSRC = server.c
CSRC = client.c
UTILS = minitalk_utilis.c

SERVER = server
CLIENT = client

PRINTF = printf/libftprintf.a

NAME = $(SERVER) $(CLIENT)

RM = rm -f

all: $(NAME)

$(NAME): $(SSRC) $(CSRC)
	@	make -C printf/
	@	$(CC) $(CFLAGS) $(SSRC) $(UTILS) $(PRINTF) -o $(SERVER)
	@	$(CC) $(CFLAGS) $(CSRC) $(UTILS) $(PRINTF) -o $(CLIENT)
	@	echo "\033[32m make: OK \033[0m"

clean:
	@	make clean -C printf/ 
	@	echo "\033[32m clean: OK \033[0m"

fclean: clean
	@	$(RM) $(SERVER) $(CLIENT) $(PRINTF)
	@	echo "\033[32m fclean: OK \033[0m"

re: fclean all

.PHONY: clean fclean re all
