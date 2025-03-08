#include "minitalk_bonus.h"

static int ft_atoi(const char *str)
{
    long result;
    int sign;
    
    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return ((int)(result * sign));
}

volatile sig_atomic_t g_ack_received = 0;

void client_handler(int signum)
{
    if (signum == SIGUSR1)
        g_ack_received = 1;
}

void send_char(int pid, unsigned char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        g_ack_received = 0;
        if (kill(pid, (c & (1 << bit)) ? SIGUSR2 : SIGUSR1) == -1)
        {
            ft_printf("Error: Failed to send signal\n");
            exit(1);
        }
        while (!g_ack_received)
            pause();
        bit--;
    }
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    int pid;
    char *message;

    if (argc != 3)
    {
        ft_printf("Usage: %s <pid> <message>\n", argv[0]);
        return (1);
    }
    sa.sa_handler = client_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        ft_printf("Error: Failed to set up signal handler\n");
        return (1);
    }
    pid = ft_atoi(argv[1]);
    if (pid <= 0)
    {
        ft_printf("Error: Invalid PID\n");
        return (1);
    }
    message = argv[2];
    while (*message)
        send_char(pid, *message++);
    send_char(pid, '\n');
    return (0);
}
