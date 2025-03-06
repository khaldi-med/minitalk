#include "./printf/ft_printf.h"
#include "minitalk.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static unsigned char	g_char = 0;

void	signal_handler_server(int signum)
{
	static int	i = 0;

	if (signum == SIGUSR2)
		g_char |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_printf("%c", g_char);
		g_char = 0;
		i = 0;
	}
}

void	decode_message(int signal)
{
	signal_handler_server(signal);
}

void	receive_char(int signal)
{
	signal_handler_server(signal);
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	sa.sa_handler = signal_handler_server;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	// Register both SIGUSR1 and SIGUSR2 handlers
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR1 handler\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR2 handler\n");
		exit(1);
	}
	
	ft_printf("Server is ready to receive messages...\n");
	while (1)
		pause();
	return (0);
}
