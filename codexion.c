#include "header/codexion.h"

static const char *scheduler_to_str(t_scheduler s)
{
    if (s == FIFO_MODE)
        return ("fifo");
    else if (s == EDF_MODE)
        return ("edf");
    return ("Invalid");
}
static void print_params (t_parameters *parameters)
{
    printf("Coders: %d\n",  parameters->coders);
    printf("Burnout: %ld\n",  parameters->time_to_burnout);
    printf("Compile: %ld\n",  parameters->time_to_compile);
    printf("Debug: %ld\n",  parameters->time_to_debug);
    printf("Refactor: %ld\n",  parameters->time_to_refactor);
    printf("Required: %ld\n",  parameters->required_compiles);
    printf("Cooldown: %ld\n",  parameters->time_to_cooldown);
    printf("Scheduler: %s\n", scheduler_to_str(parameters->scheduler));
}


int main(int argc, char **argv)
{
    t_parameters params;
    if (argc != 9)
        fprintf(stderr,"Invalid number of arguments!\n");
    else if (!parse_numeric_args(argv, &params) || !parse_scheduler(argv[8], &params))
        fprintf(stderr, "Invalid argument. Enter a valid input\n");
    print_params(&params);
    return 0;
}