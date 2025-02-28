#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "catch SIGUSR1!\n", 15);
	else if (signum == SIGUSR2)
		write(1, "catch SIGUSR2!\n", 15);
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
