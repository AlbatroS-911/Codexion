#include "codexion.h"

int start_coders (t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->parameters.coders)
	{
		if (pthread_create(&sim->threads[i], NULL, coder_routine, &sim->coders[i]) != 0)
			return (0);
		sim->started++;
		i++;
	}
	return(1);
}

int start_monitor(t_simulation *sim)
{
	if (pthread_create(&sim->monitor, NULL,  monitor_routine, sim) != 0)
		return (0);
	sim->monitor_started = 1;
	return (1);
}

int start_threads(t_simulation *sim)
{
	if (start_monitor(sim) && start_coders(sim))
		return (1);
	set_stop_flag(sim);
	join_threads(sim);
	return (0);
}

void join_threads(t_simulation *sim)
{
	int i;

	i = 0;
	if (sim->monitor_started)
		pthread_join(sim->monitor, NULL);
	while (i < sim->threads)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
}