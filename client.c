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
		if (res == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac == 3)
	{
		pid = atoi(av[1]);
		if (!(pid <= 9 && pid >= 0))
		{
			write(1, "The argements not valide!", 24);
			exit(0);
		}
		while (av[2][i])
		{
			to_bit(pid, av[2][i]);
			i++;
		}
	}
	else
	{
		write(1, "The argements not valide!", 24);
		exit(0);
	}
}
