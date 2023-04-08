/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:38:32 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/08 20:25:58 by dateixei         ###   ########.fr       */
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
	pthread_mutex_destroy(&data()->mutex.times_eatean);
	i = -1;
	while (++i < data()->nbr_philo)
		pthread_mutex_destroy(&data()->mutex.forks[i]);
	free(data()->eat_time);
	free(data()->mutex.forks);
}

void	print_event(int id, int cod)
{
	long	cur_time;

	// usleep(data()->times[t_sleep] * 1000);
	pthread_mutex_lock(&data()->mutex.print);
	cur_time = get_timestamp(data()->start_time); //Need to be tested inside and outside
	printf("%s%ldms%s %d ", LGRAY, cur_time, COLOUR_END, id);
	if (cod == 0)
	{
		printf("%sdied%s\n", RED, COLOUR_END);
		data()->ev_alive = FALSE;
	}
	else if (cod == 1)
		printf("%sis eating%s\n", GREEN, COLOUR_END);
	else if (cod == 2)
		printf("%sis sleeping%s\n", YELLOW, COLOUR_END);
	else if (cod == 3)
		printf("%sis thinking%s\n", YELLOW, COLOUR_END);
	else if (cod == 4)
		printf("%shas taken a fork%s\n", GREEN, COLOUR_END);
	pthread_mutex_unlock(&data()->mutex.print);
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

long long	my_sleep(long long t)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_timestamp(start) <= t)
	{
		if (!is_alive())
			return (0);
	}
	return (start + t);
}