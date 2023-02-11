#ifndef PHILO
# define PHILO

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef	struct s_philo
{
	int		philo_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_to_eat;
}			t_philo;

#endif