#include <signal.h>
#include <unistd.h>

int		byte_send;

int	ft_atoi(const char *str)
{
	unsigned	n;
	int			sing;
	char		*s;

	s = (char *)str;
	n = 0;
	sing = 1;
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

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(serv_pid, SIGUSR1);
		else
			kill(serv_pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		serv_pid;
	char	*str;

	if (ac != 3)
	{
		write(1, "The argemments not valide!", 25);
		return (1);
	}
	str = av[2];
	serv_pid = ft_atoi(av[1]);
	while (*str)
	{
		ft_send_bit(serv_pid, *str);
		str++;
		byte_send++;
	}
	ft_send_bit(serv_pid, '\0');
	byte_send++;
	return (0);
}
