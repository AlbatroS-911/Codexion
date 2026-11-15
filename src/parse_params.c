#include "codexion.h"

int parse_numeric_args(char **av, t_parameters *parameters)  
{
    long coders;
    long burnout;
    long compile;
    long debug;
    long refactor;
    long required;
    long cooldown;
    if (!parse_numeric_field(av[1], &coders))
        return (0);
    if (!parse_numeric_field(av[2], &burnout))
        return (0);
    if (!parse_numeric_field(av[3], &compile))
        return (0);
    if (!parse_numeric_field(av[4], &debug))
        return (0);
    if (!parse_numeric_field(av[5], &refactor))
        return (0);
    if (!parse_numeric_field(av[6], &required))
        return (0);
    if (!parse_numeric_field(av[7], &cooldown))
        return (0);
    parameters->coders = (int)coders;
    parameters->time_to_burnout = burnout;
    parameters->time_to_compile = compile;
    parameters->time_to_debug = debug;
    parameters->time_to_refactor = refactor;
    parameters->required_compiles = required;
    parameters->time_to_cooldown = cooldown;

    return(1);
}

int parse_scheduler(char *av, t_parameters *parameters)
{
    if (strcmp(av, "fifo") == 0)
    {
        parameters->scheduler = FIFO_MODE;
        return(1);
    }
    else if (strcmp(av, "edf") == 0)
    {
        parameters->scheduler = EDF_MODE;
        return(1);
    }
    return(0);
}



