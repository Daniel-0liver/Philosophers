/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:38:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/08 17:45:47 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(void)
{
	int			i;
	long long	eat_time;

	pthread_mutex_lock(&data()->mutex.still_alive);
	if (!data()->ev_alive || (data()->times_to_eat
			&& data()->times_eatean == data()->nbr_philo))
	{
		pthread_mutex_unlock(&data()->mutex.still_alive);
		return (FALSE);
	}
	i = -1;
	while (++i < data()->nbr_philo)
	{
		eat_time = data()->eat_time[i];
		if (eat_time && get_timestamp(eat_time) > data()->times[die])
		{
			print_event(i + 1, die);
			pthread_mutex_unlock(&data()->mutex.still_alive);
			return (FALSE);
		}
	}
	pthread_mutex_unlock(&data()->mutex.still_alive);
	return (TRUE);
}

int	get_fork(t_philo *p)
{
	pthread_mutex_lock(&data()->mutex.forks[p->r_fork]);
	if (!is_alive())
	{
		pthread_mutex_unlock(&data()->mutex.forks[p->r_fork]);
		return (FALSE);
	}
	pthread_mutex_lock(&data()->mutex.forks[p->l_fork]);
	if (!is_alive())
	{
		pthread_mutex_unlock(&data()->mutex.forks[p->l_fork]);
		pthread_mutex_unlock(&data()->mutex.forks[p->r_fork]);
		return (FALSE);
	}
	print_event(p->id, t_fork);
	eat_time(p);
	pthread_mutex_unlock(&data()->mutex.forks[p->l_fork]);
	pthread_mutex_unlock(&data()->mutex.forks[p->r_fork]);
	return (TRUE);
}

void	eat_time(t_philo *p)
{
	pthread_mutex_lock(&data()->mutex.still_alive);
	data()->eat_time[p->id - 1] = get_timestamp(0);
	pthread_mutex_unlock(&data()->mutex.still_alive);
	print_event(p->id, eat);
	my_sleep(data()->times[eat]);
	if (++p->meals == data()->times_to_eat)
	{
		pthread_mutex_lock(&data()->mutex.still_alive);
		data()->times_eatean++;
		pthread_mutex_unlock(&data()->mutex.still_alive);
	}
}
