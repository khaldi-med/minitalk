#ifndef MINITALK_H
# define MINITALK_H

# include "./printf/ft_printf.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *str);
void	ft_send_bit(int serv_pid, char c);
void	signal_handler_client(int signal);
void	sig_handler(int signum);

#endif
