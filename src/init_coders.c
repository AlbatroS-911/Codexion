#include "codexion.h"

int init_single_coder(t_coder *coder, t_simulation *sim, int id)
{
    coder->id = id;
    coder->simulation = sim;
    coder->last_compile_start = 0;
    coder->compiles_dones = 0;
    return(pthread_mutex_init(&coder->state_lock, NULL) == 0);
}

int init_coders(t_simulation *sim)
{
    int i;
    int total_coders;

    total_coders = sim->parameters.coders;
    sim->coders = malloc(sizeof(t_coder) * total_coders);
    if (sim->coders == NULL)
        return (0);
    sim->threads = malloc(sizeof(pthread_t) * total_coders);
    if (sim->threads == NULL)
        return (0);
    i = 0;
    while (i < total_coders)
    {
        if (!init_single_coder(&sim->coders[i], sim, i + 1))
            return (0);
        sim->coders_ready++;
        i++;
    }
    return (0);
}