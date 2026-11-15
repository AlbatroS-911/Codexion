#include "codexion.h"

void	set_last_compile_start(t_coder *coder, long timestamp)
{
	pthread_mutex_lock(&coder->state_lock);
	coder->last_compile_start = timestamp;
	pthread_mutex_unlock(&coder->state_lock);
}

long	get_last_compile_start(t_coder *coder)
{
	long	timestamp;

	pthread_mutex_lock(&coder->state_lock);
	timestamp = coder->last_compile_start;
	pthread_mutex_unlock(&coder->state_lock);
	return (timestamp);
}

void	increment_compiles_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_lock);
	coder->compiles_dones++;
	pthread_mutex_unlock(&coder->state_lock);
}

long	get_deadline(t_coder *coder)
{
	long	deadline;

	pthread_mutex_lock(&coder->state_lock);
	deadline = coder->last_compile_start + coder->simulation->parameters.time_to_burnout;
	pthread_mutex_unlock(&coder->state_lock);
	return (deadline);
}
long get_compiles_done(t_coder *coder)
{
	long	compiles_done;

	pthread_mutex_lock(&coder->state_lock);
	compiles_done = coder->compiles_dones;
	pthread_mutex_unlock(&coder->state_lock);
	return (compiles_done);
}

