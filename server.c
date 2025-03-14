/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:47:37 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/14 02:07:25 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct
{
	pid_t pid;      // Client process ID
	int bit_count;  // Tracks which bit position we're on (0-7)
	char c;         // Character being built
	int char_count; // Count of characters received from this client
}			t_client;

// Global array to track client states - allowed per project requirements
static t_client g_clients[1024]; // Support up to 1024 simultaneous clients
static int	g_total_clients = 0;

// Find client index in the array by PID, returns -1 if not found
int	find_client(pid_t pid)
{
	int	i;

	i = 0;
	while (i < g_total_clients)
	{
		if (g_clients[i].pid == pid)
			return (i);
		i++;
	}
	return (-1);
}

// Add a new client to the array
int	add_client(pid_t pid)
{
	if (g_total_clients >= 1024)
		return (-1); // Array is full
	g_clients[g_total_clients].pid = pid;
	g_clients[g_total_clients].bit_count = 0;
	g_clients[g_total_clients].c = 0;
	g_clients[g_total_clients].char_count = 0;
	return (g_total_clients++);
}

void	ft_sighandler(int signum, siginfo_t *info, void *context)
{
	int			client_idx;
	t_client	*client;

	(void)context;
	// Find or create client state based on PID
	client_idx = find_client(info->si_pid);
	if (client_idx == -1)
		client_idx = add_client(info->si_pid);
	if (client_idx == -1) // Handle the case where we can't add more clients
		return ;
	client = &g_clients[client_idx];
	// Left shift to make room for the next bit
	client->c <<= 1;
	// Add a bit if SIGUSR2 was received (matches your original logic)
	if (signum == SIGUSR2)
		client->c |= 1;
	client->bit_count++;
	// If we've received all 8 bits (a complete character)
	if (client->bit_count == 8)
	{
		// Handle null terminator (message end)
		if (client->c == '\0')
		{
			ft_printf("Client %d: %d characters received.\n",
						client->pid,
						client->char_count);
			// Reset character count for new message
			client->char_count = 0;
		}
		else
		{
			// Write the character and increment count
			write(1, &client->c, 1);
			client->char_count++;
		}
		// Reset for next character
		client->c = 0;
		client->bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	// Initialize the sigaction structure
	sig.sa_sigaction = ft_sighandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get sender information
	// Print server PID so clients know where to send signals
	ft_printf("Server PID: %d\n", getpid());
	// Register signal handlers
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	// Infinite loop - wait for signals
	while (1)
		pause();
	return (0);
}
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
// //
// int	main(void)
// {
// 	struct sigaction	sig;
//
// 	//
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
// //
// typedef struct
// {
// 	pid_t	pid;
// 	int		bit_count;
// 	char	current_char;
// }			ClientState;
// //
// // Global variables (allowed by the subject)
// static ClientState clients[1024]; // Simple array to track clients
// static int	total_clients = 0;
// //
// // Signal handler
// void	handle_signal(int sig, siginfo_t *info, void *context)
// {
// 	pid_t		sender_pid;
// 	int			client_idx;
// 	ClientState	*client;
//
// 	//
// 	(void)context;
// 	sender_pid = info->si_pid;
// 	// Find or create client state
// 	client_idx = -1;
// 	for (int i = 0; i < total_clients; i++)
// 	{
// 		if (clients[i].pid == sender_pid)
// 		{
// 			client_idx = i;
// 			break ;
// 		}
// 	}
// 	// New client
// 	if (client_idx == -1)
// 	{
// 		client_idx = total_clients++;
// 		clients[client_idx].pid = sender_pid;
// 		clients[client_idx].bit_count = 0;
// 		clients[client_idx].current_char = 0;
// 	}
// 	// Update the client's character
// 	client = &clients[client_idx];
// 	client->current_char |= (sig == SIGUSR1 ? 0 : 1) << client->bit_count;
// 	client->bit_count++;
// 	// Check if full byte received
// 	if (client->bit_count == 8)
// 	{
// 		if (client->current_char == '\0')
// 		{
// 			write(1, "\n", 1);
// 		}
// 		else
// 		{
// 			write(1, &client->current_char, 1);
// 		}
// 		// Reset client state
// 		client->bit_count = 0;
// 		client->current_char = 0;
// 	}
// }
// //
// int	main(void)
// {
// 	struct sigaction	sa;
//
// 	//
// 	sa.sa_sigaction = handle_signal;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGUSR1, &sa, NULL);
// 	sigaction(SIGUSR2, &sa, NULL);
// 	write(1, "Server PID: ", 12);
// 	ft_printf("PID: %d\n", getpid());
// 	write(1, "\n", 1);
// 	while (1)
// 		pause();
// 	return (0);
// }
