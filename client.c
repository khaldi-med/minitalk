/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:12:46 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/15 01:27:43 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_success(int sigalnum)
{
	(void)sigalnum;
	ft_printf("\033[32;1m✅✅DUDE MESSAGE PROCCESS SUCCESS...✅✅\n");
}

void	ft_message(int pid, unsigned char s)
{
	int	i;
	int	n;
	int	c;

	i = 0;
	n = 128;
	while (i < 8)
	{
		c = s / n;
		if (c == 0)
			kill(pid, SIGUSR2);
		else
		{
			kill(pid, SIGUSR1);
			s = s % n;
		}
		usleep(100);
		n /= 2;
		i++;
	}
}

int	main(int ac, char **av)
{
	int	j;
	int	pid;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, ft_success);
	j = 0;
	while (av[2][j])
	{
		ft_message(pid, av[2][j]);
		j++;
	}
	if (av[2][j] == '\0')
		ft_message(pid, av[2][j]);
}
