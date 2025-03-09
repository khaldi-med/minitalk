#include "minitalk.h"
#include "printf/ft_printf.h"

int		byte_send = 0;

void	ft_error(void)
{
	write(2, "There is an ERORR!\n", 18);
	exit(1);
}

void	ft_send_bit(int serv_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			if ((kill(serv_pid, SIGUSR2)) == -1)
				ft_error();
			else if ((kill(serv_pid, SIGUSR1)) == -1)
				ft_error();
		usleep(400);
		i--;
	}
}

int	main(int ac, char **av)
{
	int		serv_pid;
	char	*str;
	int		i;

	i = 0;
	if (ac != 3 || av[1][0] == 0 || av[2][0] == 0)
	{
		write(1, "The argemment not valide\n", 25);
		return (1);
	}
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			ft_error();
		i++;
	}
	serv_pid = ft_atoi(av[1]);
	if (serv_pid <= 0)
		ft_error();
	str = av[2];
	while (*str)
	{
		ft_send_bit(serv_pid, *str);
		str++;
		byte_send++;
	}
	ft_send_bit(serv_pid, '\0');
	ft_printf("%d char sent.\n", byte_send);
	return (0);
}
