CC = cc
CFLAGS = -Wall -Wextra -Werror
SSRC = server.c
CSRC = client.c

SERVER = server
CLIENT = client

SSRC_B = server_bonus.c 
CSRC_B = client_bonus.c

SERVER_B = server_bonus
CLIENT_B = client_bonus

PRINTF = printf/libftprintf.a

NAME = $(SERVER) $(CLIENT)

BONUS = $(SERVER_B) $(CLIENT_B)

RM = rm -f

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(SSRC) $(CSRC)
	@	make -C printf/
	@	$(CC) $(CFLAGS) $(SSRC) $(PRINTF) -o $(SERVER)
	@	$(CC) $(CFLAGS) $(CSRC) $(PRINTF) -o $(CLIENT)
	@	echo "\033[32m make: OK \033[0m"

$(BONUS): $(SSRC_B) $(CSRC_B)
	@	make -C printf/
	@	$(CC) $(CFLAGS) $(SSRC_B) $(PRINTF) -o $(SERVER_B)
	@	$(CC) $(CFLAGS) $(CSRC_B) $(PRINTF) -o $(CLIENT_B)
	@	echo "\033[32m make bonus: OK \033[0m"

clean:
	@	make clean -C printf/ 
	@	echo "\033[32m clean: OK \033[0m"

fclean: clean
	@	$(RM) $(SERVER) $(CLIENT) $(PRINTF)
	@	$(RM) $(SERVER_B) $(CLIENT_B)
	@	echo "\033[32m fclean: OK \033[0m"

re: fclean all

.PHONY: clean fclean re all
