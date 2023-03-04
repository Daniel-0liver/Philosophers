#ifndef PHILO
# define PHILO

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef	struct s_philo
{
	int					i;
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_to_eat;
	int					error;
	pthread_mutex_t		philo_mutex;
}			t_philo;

typedef struct s_forks
{
	int					nbr_forks;
	pthread_t			right_forks;
	pthread_t			left_forks;
}			t_forks;

//Utils
int		ft_atoi(char *str, t_philo *philo);
void	is_non_number(char **argv, t_philo *philo);

#endif