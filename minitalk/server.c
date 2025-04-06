/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:47:37 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/27 22:23:32 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sighandler(int signum, siginfo_t *info, void *context)
{
	static int	c_pid;
	static char	c;
	static int	bit_count;

	(void)context;
	c_pid = info->si_pid;
	if (info->si_pid != c_pid)
	{
		c = 0;
		bit_count = 0;
		c_pid = info->si_pid;
	}
	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = ft_sighandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGUSR1, &sig, NULL);
	while (1)
		pause();
	return (0);
}
