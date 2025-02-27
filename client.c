#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// void	to_bit(int pid, char c)
// {
// 	int	i;
// 	int	ref;
// 	int	res;
//
// 	i = 0;
// 	ref = 1;
// 	while (i < 8)
// 	{
// 		res = (c >> i) & 1;
// 		if (res)
// 			kill(pid, SIGUSR1);
// 		else
// 			kill(pid, SIGUSR2);
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	int		pid;
	char	*str;

	if (ac == 3)
	{
		str = av[2];
		pid = atoi(av[1]);
		if (*str == 'a')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
	}
	return (0);
}
