#include "printf/ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		byte_send = 0;

int	ft_atoi(const char *str)
{
	unsigned	n;
	int			sing;
	char		*s;

	n = 0;
	sing = 1;
	s = (char *)str;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sing *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = (n * 10) + (*s - '0');
		s++;
	}
	return (sing * n);
}

void	ft_send_bit(int serv_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(serv_pid, SIGUSR2);
		else
			kill(serv_pid, SIGUSR1);
		usleep(400);
		i--;
	}
}

void	ft_error(void)
{
	write(2, "There is an ERORR!\n", 18);
	exit(1);
}

int	main(int ac, char **av)
{
	int		serv_pid;
	char	*str;

	if (ac != 3 || av[1][0] == 0 || av[2][0] == 0)
	{
		write(1, "The argemment not valide\n", 25);
		return (1);
	}
	serv_pid = ft_atoi(av[1]);
	if (serv_pid < 0)
		ft_error();
	str = av[2];
	while (*str)
	{
		ft_send_bit(serv_pid, *str);
		str++;
		byte_send++;
	}
	ft_send_bit(serv_pid, '\0');
	printf("%d char sent.\n", byte_send);
	return (0);
}
