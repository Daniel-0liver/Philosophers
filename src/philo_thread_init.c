/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:52:16 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/02 16:52:32 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_philo **philo, pthread_t **tid)
{
	int	i;

	*philo = (t_philo *) malloc(sizeof(t_philo) * data()->nbr_philo);
	*tid = (pthread_t *) malloc(sizeof(pthread_t) * data()->nbr_philo);
	i = -1;
	while (++i < data()->nbr_philo)
		(*philo)[i].meals = 0;
	data()->eat_time = malloc(sizeof(struct timeval) * data()->nbr_philo);
	i = -1;
	while (++i < data()->nbr_philo)
		data()->eat_time[i] = 0;
	data()->ev_alive = TRUE;
	data()->times_eatean = 0;
	pthread_mutex_init(&data()->mutex.print, NULL);
	pthread_mutex_init(&data()->mutex.still_alive, NULL);
	pthread_mutex_init(&data()->mutex.times_eatean, NULL);
	data()->mutex.forks = malloc(sizeof(pthread_mutex_t) * data()->nbr_philo);
	i = -1;
	while (++i < data()->nbr_philo)
		pthread_mutex_init(&data()->mutex.forks[i], NULL);
}

void	init_thread()
{
	t_philo		*philo;
	pthread_t	*tid;

	init_var(&philo, &tid);
	free_progam();
	free(philo);
	free(tid);
}