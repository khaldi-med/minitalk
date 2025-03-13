/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:47:37 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/11 21:27:32 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		char_count;

void	ft_sighandler(int signum)
{
	static char	c;
	static int	bit_count;

	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
		{
			ft_printf("\n%d char has been catched!\n", char_count);
			char_count = 0;
		}
		else
		{
			write(1, &c, 1);
			char_count++;
		}
		c = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_handler = ft_sighandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGUSR1, &sig, NULL);
	while (1)
		pause();
	return (0);
}
