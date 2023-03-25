#ifndef PHILO
# define PHILO

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_table
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_to_eat;
	int					error;
}			t_table;

typedef	struct s_philo
{
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		mutex;
}			t_philo;

typedef struct s_data
{
	int					time_sec;
	t_philo				*philo;
	t_table				table;
	struct	timeval		time;
}			t_data;

//Utils
int		ft_atoi(char *str, t_data *data);
int		get_timestamp(t_data *data);
void	is_non_number(char **argv, t_data *data);

#endif