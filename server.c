#include "printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

int		count = 0;
void	sig_handler(int signum)
{
	static char	bit_catched;
	static int	bit_count;

	bit_catched <<= 1;
	if (signum == SIGUSR2)
		bit_catched |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (bit_catched == '\0')
		{
			ft_printf("\n%d char has been catched!\n", count);
			count = 0;
		}
		else
		{
			write(1, &bit_catched, 1);
			count++;
		}
		bit_catched = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("Server PID: %d\n", getpid());
	sig.sa_handler = sig_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
