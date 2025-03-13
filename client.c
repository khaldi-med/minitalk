/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:12:46 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/13 01:33:27 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(void)
{
	write(2, "There is an ERROR!\n", 19);
	exit(1);
}

void	ft_send_bit(int serv_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			if ((kill(serv_pid, SIGUSR2)) == -1)
				ft_error();
		}
		else if ((kill(serv_pid, SIGUSR1)) == -1)
			ft_error();
		usleep(400);
		i--;
	}
}

int	ft_check_pid(char *str)
{
	int	serv_pid;

	serv_pid = ft_atoi(str);
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error();
		str++;
	}
	if (serv_pid <= 0)
		ft_error();
	return (serv_pid);
}

int	main(int ac, char **av)
{
	int		byte_sent;
	int		pid;
	char	*str;

	if (ac != 3 || av[1][0] == 0 || av[2][0] == 0)
		ft_error();
	pid = ft_check_pid(av[1]);
	str = av[2];
	byte_sent = 0;
	while (*str)
	{
		ft_send_bit(pid, *str);
		str++;
		byte_sent++;
	}
	ft_send_bit(pid, '\0');
	ft_printf("%d char sent.\n", byte_sent);
	return (0);
}
