#include "codexion.h"

void log_event(t_simulation *sim, int coder_id, const char *message)
{
	long timestamp;
	pthread_mutex_lock(&sim->log_lock);
	if (!simulation_stopped(sim) || strcmp(message, MSG_BURNED_OUT) == 0)
	{
		timestamp = current_ms(sim);
		printf("%ld %d %s\n", timestamp, coder_id, message);
	}
	pthread_mutex_unlock(&sim->log_lock);
}

