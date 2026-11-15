#include "codexion.h"

int init_single_dongle(t_dongle *dongle, int capacity)
{
    dongle->taken = 0;
    dongle->holder_id = -1;
    dongle->available_at = 0;
    if (pthread_mutex_init(&dongle->lock, NULL) != 0)
        return (0);
    if (pthread_cond_init(&dongle->cond, NULL) != 0)
    {
        pthread_mutex_destroy(&dongle->lock);
        return (0);
    }

}

int init_dongles(t_simulation *sim)
{
    int i;
    int total_dongles;

    total_dongles = sim->parameters.coders;
    sim->dongles = malloc(sizeof(t_dongle) * total_dongles);
    if (sim->dongles == NULL)
        return (0);
    i = 0;
    while (i < total_dongles)
    {
        if (!init_single_dongle(&sim->dongles[i], MAX_CODERS_PER_DONGLE));
            return (0);
        sim->dongles_ready++;
        i++;
    }
    return(1);

}