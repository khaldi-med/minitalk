/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:47:37 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/14 00:58:37 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// pid_t	cl_pid;
// void	ft_sighandler(int signum, siginfo_t *info, void *context)
// {
// 	static int	char_count;
// 	static char	c;
// 	static int	bit_count;
//
// 	(void)context;
// 	if (cl_pid == 0)
// 		cl_pid = info->si_pid;
// 	if (info->si_pid != cl_pid)
// 	{
// 		cl_pid = 0;
// 		c = 0;
// 		cl_pid = info->si_pid;
// 	}
// 	c <<= 1;
// 	if (signum == SIGUSR2)
// 		c |= 1;
// 	bit_count++;
// 	if (bit_count == 8)
// 	{
// 		if (c == '\0')
// 		{
// 			ft_printf("\n%d char has been catched!\n", char_count);
// 			char_count = 0;
// 		}
// 		else
// 		{
// 			write(1, &c, 1);
// 			char_count++;
// 		}
// 		c = 0;
// 		bit_count = 0;
// 	}
// }
//
// int	main(void)
// {
// 	struct sigaction	sig;
//
// 	sig.sa_sigaction = ft_sighandler;
// 	sigemptyset(&sig.sa_mask);
// 	sig.sa_flags = SA_SIGINFO;
// 	ft_printf("PID: %d\n", getpid());
// 	sigaction(SIGUSR2, &sig, NULL);
// 	sigaction(SIGUSR1, &sig, NULL);
// 	while (1)
// 		pause();
// 	return (0);
// }

typedef struct
{
	pid_t	pid;
	int		bit_count;
	char	current_char;
}			ClientState;

// Global variables (allowed by the subject)
static ClientState clients[1024]; // Simple array to track clients
static int	total_clients = 0;

// Signal handler
void	handle_signal(int sig, siginfo_t *info, void *context)
{
	pid_t		sender_pid;
	int			client_idx;
	ClientState	*client;

	(void)context;
	sender_pid = info->si_pid;
	// Find or create client state
	client_idx = -1;
	for (int i = 0; i < total_clients; i++)
	{
		if (clients[i].pid == sender_pid)
		{
			client_idx = i;
			break ;
		}
	}
	// New client
	if (client_idx == -1)
	{
		client_idx = total_clients++;
		clients[client_idx].pid = sender_pid;
		clients[client_idx].bit_count = 0;
		clients[client_idx].current_char = 0;
	}
	// Update the client's character
	client = &clients[client_idx];
	client->current_char |= (sig == SIGUSR1 ? 0 : 1) << client->bit_count;
	client->bit_count++;
	// Check if full byte received
	if (client->bit_count == 8)
	{
		if (client->current_char == '\0')
		{
			write(1, "\n", 1);
		}
		else
		{
			write(1, &client->current_char, 1);
		}
		// Reset client state
		client->bit_count = 0;
		client->current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "Server PID: ", 12);
	ft_printf("PID: %d\n", getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
