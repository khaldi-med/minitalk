#ifndef MINITALK_H
# define MINITALK_H

# include "./printf/ft_printf.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

/*
 * Client function prototypes
 */
void	send_message(int pid, char *message);
void	send_char(int pid, unsigned char c);
void	signal_handler_client(int signal);

/*
 * Server function prototypes
 */
void	signal_handler_server(int signal);
void	decode_message(int signal);
void	receive_char(int signal);

#endif
