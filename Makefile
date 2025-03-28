# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 03:01:51 by mohkhald          #+#    #+#              #
#    Updated: 2025/03/28 22:29:09 by mohkhald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRV_S = server.c

CLNT_S = client.c

UTILIS = minitalk_utilis.c

SERVER = server

CLIENT = client

PRINTF = ft_printf/libftprintf.a

NAME = $(SERVER) $(CLIENT)

RM = rm -Rf

all: $(NAME)

$(NAME): $(SRV_S) $(CLNT_S) 
	@make -C ft_printf/
	@$(CC) $(CFLAGS) $(SRV_S) $(UTILIS) $(PRINTF) -o $(SERVER)
	@$(CC) $(CFLAGS) $(CLNT_S) $(UTILIS) $(PRINTF) -o $(CLIENT)

clean: 
	@make clean -C ft_printf/

fclean: clean
	@$(RM) $(SERVER) $(CLIENT) $(PRINTF)

re: fclean all

.PHONY: clean fclean re all
