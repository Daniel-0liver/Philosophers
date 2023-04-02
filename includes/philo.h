#ifndef PHILO
# define PHILO

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0
# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define COLOUR_END "\033[0m"

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
	int					id;
	int					error;
	int					forks;
	int					life;
	int					times_eated;
	int					t_last_meal;
	int					t_last_sleep;
	int					t_last_think;
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		mutex;
}			t_philo;

typedef struct s_data
{
	int					dead;
	int					count;
	int					is_running;
	t_philo				*philo;
	t_table				table;
	struct	timeval		time;
	pthread_mutex_t		data_race;
}			t_data;

//Utils
int		get_timestamp(t_data *data);
int		ft_atoi(char *str, t_data *data);
void	is_non_number(char **argv, t_data *data);
void	check_args(t_data *data, int argc, char **argv);

//Thread Init
void	*start_run(t_philo *p);
void	*verify_run(void *philo);
void	init_thread(t_data *data);
int		is_dead(t_philo *philo);
int		can_start_run(t_data *data, int id);

#endif