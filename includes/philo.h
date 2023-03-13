#ifndef PHILO
# define PHILO

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct s_philo
{
	int					i;
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_to_eat;
	int					error;
	int					time_sec;
	pthread_t			philo_mutex;
	struct	timeval		time;
}			t_philo;



//Utils
int		ft_atoi(char *str, t_philo *philo);
int		get_timestamp(t_philo *philo);
void	is_non_number(char **argv, t_philo *philo);


#endif