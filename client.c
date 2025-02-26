#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	to_bit(int pid, char c)
{
	int	i;
	int	ref;
	int	res;

	i = 0;
	ref = 1;
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
	int		i;
	int		pid;
	char	*str;

	i = 0;
	if (ac == 3)
	{
		str = av[2];
		pid = atoi(av[1]);
		if (pid < 0)
		{
			write(1, "The PID not valide!", 24);
			return (1);
		}
		while (*str)
		{
			to_bit(pid, *str);
			str++;
		}
	}
	else
	{
		write(1, "The argements not valide!", 24);
		return (1);
	}
}
