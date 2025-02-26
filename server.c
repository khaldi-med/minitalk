#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("The process ID is %d\n", pid);
	return (0);
}
