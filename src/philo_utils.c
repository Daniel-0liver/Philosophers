/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:38:32 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/02 16:47:48 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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