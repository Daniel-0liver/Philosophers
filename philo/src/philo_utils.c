/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:38:32 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/10 23:50:39 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(long long start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

void	free_progam(void)
{
	int	i;

	pthread_mutex_destroy(&data()->mutex.print);
	pthread_mutex_destroy(&data()->mutex.still_alive);
	i = -1;
	while (++i < data()->nbr_philo)
		pthread_mutex_destroy(&data()->mutex.forks[i]);
	free(data()->eat_time);
	free(data()->mutex.forks);
}

void	print_event(int id, int cod)
{
	long	t;

	t = get_timestamp(data()->start_time);
	if (cod == 0)
	{
		pthread_mutex_lock(&data()->mutex.print);
		printf("%ld ms %d %sdied%s\n", t, id, RED, COLOUR_END);
		data()->ev_alive = FALSE;
		pthread_mutex_unlock(&data()->mutex.print);
	}
	else if (cod == 1)
		printf("%ld ms %d %sis eating%s\n", t, id, GREEN, COLOUR_END);
	else if (cod == 2)
		printf("%ld ms %d %sis sleeping%s\n", t, id, YELLOW, COLOUR_END);
	else if (cod == 3)
		printf("%ld ms %d %sis thinking%s\n", t, id, YELLOW, COLOUR_END);
	else if (cod == 4)
		printf("%ld ms %d %shas taken a fork%s\n", t, id, GREEN, COLOUR_END);
}

void	right_left_fork(t_philo *p)
{
	int	tmp;

	if (p->id == 1)
	{
		p->l_fork = data()->nbr_philo - 1;
		p->r_fork = p->id - 1;
	}
	else
	{
		p->l_fork = p->id - 2;
		p->r_fork = p->id - 1;
	}
	if (p->id % 2 == 0)
	{
		tmp = p->l_fork;
		p->l_fork = p->r_fork;
		p->r_fork = tmp;
	}
}

void	time_counter(int t, t_philo *p)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_timestamp(start) <= t)
	{
		if (!is_alive(p))
			return ;
	}
}
