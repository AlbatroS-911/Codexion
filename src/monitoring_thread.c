#include "codexion.h"

int monitor_routine(t_simulation *sim)
{
	int i;

	while (!simulation_stopped(sim))
	{
		i = 0;
		while (i < sim->parameters.coders)
		{
			if (read_deadline(&sim->coders[i]) < current_ms(sim))
			{
				log_event(sim, sim->coders[i].id, MSG_BURNED_OUT);
				set_stop_flag(sim);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}