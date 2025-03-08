#include "minitalk_bonus.h"

volatile sig_atomic_t g_bit_count = 0;
volatile sig_atomic_t g_current_char = 0;
volatile sig_atomic_t g_sender_pid = 0;

void server_handler(int signo, siginfo_t *info, void *context)
{
    (void)context;

    if (g_sender_pid == 0)
        g_sender_pid = info->si_pid;

    g_current_char = g_current_char << 1;
    if (signo == SIGUSR2)
        g_current_char |= 1;

    g_bit_count++;
    if (g_bit_count == 8)
    {
        char tmp_char = (char)g_current_char;
        if (tmp_char == 0)
            write(1, "\n", 1);
        else
            write(1, &tmp_char, 1);
        g_bit_count = 0;
        g_current_char = 0;
    }

    if (kill(g_sender_pid, SIGUSR1) == -1)
    {
        ft_printf("Error: Failed to send acknowledgment\n");
        exit(1);
    }
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = server_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error: Failed to set up signal handlers\n");
        return (1);
    }

    ft_printf("Server PID: %d\n", getpid());
    while (1)
        pause();
    return (0);
}
