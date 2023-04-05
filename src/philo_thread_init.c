/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:52:16 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/05 22:59:57 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alloc_var_and_mutexes(t_philo **philo, pthread_t **tid)
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

void	*start_dinner(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	if (data()->nbr_philo == 1)
	{
		usleep(data()->times[die] * 1000);
		print_event(p->id, die);
		return (0);
	}
	data()->eat_time[p->id - 1] = get_timestamp(0);
	while (TRUE)
	{
		if (get_timestamp(data()->start_time) >= data()->times[die])
		{
			pthread_mutex_lock(&data()->mutex.print);
			print_died(p->id);
			return (0);
		}
		usleep(1000);
		if (data()->ev_alive)
			print_event(p->id, t_fork);
		else
			return (0);
		usleep(1000);
		if (data()->ev_alive)
			print_event(p->id, eat);
		else
			return (0);
		usleep(1000);
		if (data()->ev_alive)
			print_event(p->id, t_sleep);
		else
			return (0);
		usleep(1000);
		if (data()->ev_alive)
			print_event(p->id, think);
		else
			return (0);
		usleep(1000);
	}
	return (NULL);
}

void	init_thread()
{
	t_philo		*philo;
	pthread_t	*tid;
	int			i;

	alloc_var_and_mutexes(&philo, &tid);
	data()->start_time = get_timestamp(0);
	i = -1;
	while (++i < data()->nbr_philo)
	{
		philo[i].id = i + 1;
		pthread_create(&tid[i], NULL, start_dinner, (void *) &philo[i]);
	}
	i = -1;
	while(++i < data()->nbr_philo)
		pthread_join(tid[i], NULL);
	free_progam();
	free(philo);
	free(tid);
}
