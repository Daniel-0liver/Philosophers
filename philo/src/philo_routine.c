/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:38:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/16 23:28:07 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *p)
{
	pthread_mutex_lock(&data()->mutex.still_alive);
	if (!data()->ev_alive || (data()->times_to_eat
			&& data()->times_eatean == data()->nbr_philo))
	{
		pthread_mutex_unlock(&data()->mutex.still_alive);
		return (FALSE);
	}
	pthread_mutex_unlock(&data()->mutex.still_alive);
	if (data()->eat_time[p->id - 1] && get_timestamp
		(data()->eat_time[p->id - 1]) > data()->times[die])
	{
		print_event(p->id, die);
		pthread_mutex_unlock(&data()->mutex.still_alive);
		return (FALSE);
	}
	return (TRUE);
}

int	eat_time(t_philo *p)
{
	pthread_mutex_lock(&data()->mutex.forks[p->r_fork]);
	print_event(p->id, t_fork);
	pthread_mutex_lock(&data()->mutex.forks[p->l_fork]);
	print_event(p->id, t_fork);
	if (!is_alive(p))
	{
		pthread_mutex_unlock(&data()->mutex.forks[p->l_fork]);
		pthread_mutex_unlock(&data()->mutex.forks[p->r_fork]);
		return (FALSE);
	}
	print_event(p->id, eat);
	time_counter_eat(data()->times[eat], p);
	pthread_mutex_unlock(&data()->mutex.forks[p->l_fork]);
	pthread_mutex_unlock(&data()->mutex.forks[p->r_fork]);
	return (TRUE);
}

void	sleep_think_event(t_philo *p)
{
	if (++p->meals == data()->times_to_eat)
	{
		pthread_mutex_lock(&data()->mutex.still_alive);
		data()->times_eatean++;
		pthread_mutex_unlock(&data()->mutex.still_alive);
	}
	if (!is_alive(p))
		return ;
	print_event(p->id, t_sleep);
	time_counter_sleep(data()->times[t_sleep], p);
	if (!is_alive(p))
		return ;
	print_event(p->id, think);
}

void	time_counter_eat(int t, t_philo *p)
{
	struct timeval	time;
	long long		start;

	data()->eat_time[p->id - 1] = get_timestamp(0);
	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_timestamp(start) < t)
	{
		if (!is_alive(p))
			return ;
	}
}

void	time_counter_sleep(int t, t_philo *p)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_timestamp(start) < t)
	{
		if (!is_alive(p))
			return ;
	}
}
