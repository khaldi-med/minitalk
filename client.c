#include <signal.h>
#include <unistd.h>

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

void	ft_send_bit(int pid, char c)
{
	int	i;
	int	res;

	i = 0;
	while (i < 8)
	{
		res = (c >> i) & 1;
		if (res)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*str;

	if (ac != 3)
	{
		write(1, "The argemments not valide!", 25);
		return (1);
	}
	str = av[2];
	pid = ft_atoi(av[1]);
	while (*str)
	{
		ft_send_bit(pid, *str);
		str++;
	}
	return (0);
}
