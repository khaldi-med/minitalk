#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		printf("The argemments not valide!");
		return (1);
	}
	str = av[2];
	pid = atoi(av[1]);
	while (*str)
		ft_send_bit(pid, *str);
	return (0);
}
