#ifndef PHILO
# define PHILO

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define LGRAY "\001\033[0;37m\002"
# define COLOUR_END "\033[0m"

enum e_time_to{
	die,
	eat,
	t_sleep,
	think,
	t_fork
};

typedef struct s_mutexes
{
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	pthread_mutex_t		still_alive;
	pthread_mutex_t		times_eatean;
}			t_mutexes;

typedef	struct s_philo
{
	int					id;
	int					meals;
}			t_philo;

typedef struct s_data
{
	int					error;
	int					times_to_eat;
	int					ev_alive;
	int					nbr_philo;
	int					times_eatean;
	long long			start_time;
	long long			*eat_time;
	long				times[3];
	t_mutexes			mutex;
}			t_data;

//Data func declaration
t_data		*data(void);

//philo_check_args
long		ft_atoi(char *str);
void		is_non_number(char **argv);
int			check_args(int argc, char **argv);

//Thread Init
void		*start_dinner(void *philo);
void		*verify_run(void *philo);
void		init_thread();
void		alloc_var_and_mutexes_var(t_philo **philo, pthread_t **tid);
int			is_dead(t_philo *philo);
int			can_start_run(t_data *data, int id);

//Utils
void		free_progam(void);
void		print_event(int id, int cod);
long long	get_timestamp(long long start_time);

#endif