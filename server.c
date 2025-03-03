#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int		count;
void	sig_handler(int signum)
{
	char	bit_catched;

	bit_catched = 0;
	if (signum == SIGUSR1)
		bit_catched <<= 1;
	else if (signum == SIGUSR2)
		bit_catched <<= 1 | 1;
	if (bit_catched == 8)
		printf("%s", &bit_catched);
}

int	main(void)
{
	struct sigaction	sig;

	printf("the pid poc is %d\n: ", getpid());
	sig.sa_handler = sig_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
