#include "codexion.h"

void	get_ordered_dongles(t_coder *coder, int *first_dongle, int *second_dongle)
{
	int id_coder;
	int left;
	int right;
	int n_coder;

	id_coder = coder->id - 1;
	n_coder = coder->simulation->parameters.coders;
	right = id_coder;
	left = (id_coder - 1 + n_coder) % n_coder;
	if (left < right)
	{
		*first_dongle = left;
		*second_dongle = right;
		return ;
	}
	*first_dongle = right;
	*second_dongle = left;
}

int compile_attempt (t_coder *coder)
{
	t_simulation		*sim;
	int								first_dongle;
	int 							second_dongle;
	long						deadline;

	sim = coder->simulation;
	get_ordered_dongles(coder, &first_dongle, &second_dongle);
	deadline = read_deadline(coder);
	if (acquire_dongle(sim, first_dongle, coder->id, deadline) == -1)
		return (-1);
	log_event(sim, coder->id, MSG_TAKEN);
	if (acquire_dongle(sim, second_dongle, coder->id, deadline) == -1)
	{
		release_dongle(sim, first_dongle);
		return(-1);
	}
	log_event(sim, coder->id, MSG_TAKEN);
	return(run_compile_phase(coder, first_dongle, second_dongle));
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!simulation_stopped(coder->simulation))
	{
		if (try_compile(coder) == -1)
			break ;
		if (sleep_interruptible(coder->simulation, coder->simulation->parameters.time_to_debug)
			== -1)
			break ;
		if (run_phase(coder->simulation, coder->id, MSG_REFACTORING,
				coder->simulation->parameters.time_to_refactor) == -1)
			break ;
	}
	return (NULL);
}