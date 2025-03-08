#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/* Required function prototypes */
int		ft_printf(const char *format, ...);

/* Client function prototypes */
void	send_char(int pid, unsigned char c);
void	client_handler(int signum);

/* Server function prototypes */
void	server_handler(int signum, siginfo_t *info, void *context);

#endif
