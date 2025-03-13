#include "minitalk.h"

t_client *find_or_create_client(t_client **clients, pid_t pid)
{
    t_client *current;
    t_client *new_client;

    if (!clients)
        return (NULL);

    // Search for existing client
    current = *clients;
    while (current)
    {
        if (current->pid == pid)
            return (current);
        current = current->next;
    }

    // Create new client if not found
    new_client = (t_client *)malloc(sizeof(t_client));
    if (!new_client)
        return (NULL);

    // Initialize new client
    new_client->pid = pid;
    new_client->bit_catched = 0;
    new_client->bit_count = 0;
    new_client->char_count = 0;
    new_client->next = *clients;

    // Add to front of list
    *clients = new_client;
    return (new_client);
}

void remove_client(t_client **clients, pid_t pid)
{
    t_client *current;
    t_client *prev;

    if (!clients || !*clients)
        return;

    current = *clients;
    prev = NULL;

    while (current)
    {
        if (current->pid == pid)
        {
            if (prev)
                prev->next = current->next;
            else
                *clients = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

