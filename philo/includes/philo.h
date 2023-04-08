/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:04:26 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/08 16:29:41 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef struct s_philo
{
	int					id;
	int					meals;
	int					l_fork;
	int					r_fork;
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
void		init_thread(void);
void		alloc_var_and_mutexes(t_philo **philo, pthread_t **tid);

//Utils
void		free_progam(void);
void		print_event(int id, int cod);
long long	get_timestamp(long long start_time);
void		right_left_fork(t_philo *p);
long long	my_sleep(long long time_to);


//Routine
int			is_alive(void);
int			get_fork(t_philo *p);
void		eat_time(t_philo *p);


#endif