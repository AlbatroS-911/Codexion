#ifndef CODEXION_H
# define CODEXION_H

#include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define MSG_TAKEN "has taken a dongle"
# define MSG_COMPILING "is compiling"
# define MSG_DEBUGGING "is debugging"
# define MSG_REFACTORING "is refactoring"
# define MSG_BURNED_OUT "burned out"

# define MAX_CODERS 5000
# define MAX_CODERS_PER_DONGLE 2
# define POLL_INTERVAL_MS 5
# define MONITOR_POLL_US 1000
# define MAX_TIME_MS INT_MAX

typedef enum e_scheduler
{
    FIFO_MODE,
    EDF_MODE
} t_scheduler;

typedef struct s_parameters
{
    int coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long required_compiles;
    long time_to_cooldown;
    t_scheduler scheduler;
} t_parameters;

typedef struct s_heap_node
{
	int coder_id;
	long primary;
	long secondary;
} t_heap_node;

typedef struct s_heap
{
	t_heap_node *nodes;
	int	size;
	int capacity;
} t_heap;

typedef struct s_dongles
{
	pthread_mutex_t lock;
	pthread_cond_t cond;
	int  taken;
	int holder_id;
	long available_at;
	t_heap waiters;

} t_dongle;

typedef struct s_simulation
{
	t_parameters		parameters;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		*threads;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	seq_lock;
	pthread_t		monitor;
	int				stop;
	int				started;
	int				monitor_started;
	int				sync_ready;
	int				dongles_ready;
	int				coders_ready;
	long			request_seq;
	struct timeval	start_time;
} t_simulation;

typedef struct s_coder
{
    int id;
	long last_compile_start;
	long compiles_dones;
	pthread_mutex_t state_lock;
	t_simulation *simulation;
} t_coder;


// Parsing utils
int char_is_digit(char c);
int is_valid_digit_string(const char *str);
int long_string(const char *str, long *out);
int parse_numeric_field(const char *str, long *out);

// Parsing functions
int parse_numeric_args(char **av, t_parameters *parameters);
int parse_scheduler(char *av, t_parameters *parameters);

// Initialisation functions
int init_single_dongle(t_dongle *dongle, int capacity);
int init_dongles(t_simulation *sim);
int init_single_coder(t_coder *coder, t_simulation *sim, int id);
int init_coders(t_simulation *sim);
int init_sync_primitives(t_simulation *sim);
int init_simulation(t_simulation *sim, t_parameters *params);

// Cleaning simulation functions
void destroy_dongles(t_simulation *sim);
void destroy_coders(t_simulation *sim);
void destroy_sync(t_simulation *sim);
void cleanup_simulation(t_simulation *sim);

// Simulation state
long	current_ms(t_simulation *sim);
long	sim_start_epoch_us(t_simulation *sim);
long	next_sequence(t_simulation *sim);
int	simulation_stopped(t_simulation *sim);
void	set_stop_flag(t_simulation *sim);


// Coder functions
void	get_ordered_dongles(t_coder *coder, int *first_dongle, int *second_dongle);
int compile_attempt (t_coder *coder);
void	*coder_routine(void *arg);

// Monitor function
int monitor_routine(t_simulation *sim);

// Thread functions
int start_coders (t_simulation *sim);
int start_monitor(t_simulation *sim);
int start_threads(t_simulation *sim);
void join_threads(t_simulation *sim);

// Coder state functions
void	set_last_compile_start(t_coder *coder, long timestamp);
long	get_last_compile_start(t_coder *coder);
void	increment_compiles_done(t_coder *coder);
long	get_deadline(t_coder *coder);
long get_compiles_done(t_coder *coder);

// Dongle functions
int acquire_dongle(t_simulation *sim, int dongle_id, int coder_id, long deadline);
void release_dongle(t_simulation *sim, int dongle_id);
int read_deadline(t_coder *coder);
int sleep_interruptible(t_simulation *sim, long duration_ms);

// Logging functions
void log_event(t_simulation *sim, int coder_id, const char *message);

#endif