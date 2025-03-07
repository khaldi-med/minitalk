#include "printf/ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int		byte_send = 0; // Global variable to count bytes sent

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
	int i = 7; // Start from the most significant bit (MSB)
	while (i >= 0)
	{
		if (c & (1 << i))            // Check if the current bit is 1
			kill(serv_pid, SIGUSR2); // Send SIGUSR2 for 1
		else
			kill(serv_pid, SIGUSR1); // Send SIGUSR1 for 0
		usleep(400);
		// Small delay to ensure the server processes the signal
		i--;
	}
}

int	main(int ac, char **av)
{
	int		serv_pid;
	char	*str;

	if (ac != 3) // Check if the correct number of arguments is provided
	{
		write(1, "Usage: ./client <server_pid> <message>\n", 38);
		return (1);
	}
	serv_pid = ft_atoi(av[1]); // Convert the server PID from string to integer
	str = av[2];               // Get the message to send
	while (*str)               // Send each character of the message
	{
		ft_send_bit(serv_pid, *str);
		str++;
		byte_send++;
	}
	ft_send_bit(serv_pid, '\0');
	// Send null terminator to indicate end of message
	printf("%d bytes sent.\n", byte_send); // Print the number of bytes sent
	return (0);
}
