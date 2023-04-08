/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:38:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/08 01:17:50 by dateixei         ###   ########.fr       */
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
			print_died(i + 1);
			return (FALSE);
		}
	}
	pthread_mutex_unlock(&data()->mutex.still_alive);
	return (TRUE);
}

int	get_fork(t_philo *p)
{
	
}