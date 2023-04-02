/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:52:16 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/02 02:59:01 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_start_run(t_data *data, int id)
{
	pthread_mutex_lock(&data->data_race);
	if (id == data->table.philo_nbr - 1)
	{
		gettimeofday(&data->time, NULL);
		data->is_running = 1;
	}
	pthread_mutex_unlock(&data->data_race);
	return (data->is_running);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_race);
	if (philo->data->dead == 0 && philo->life < get_timestamp(philo->data))
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->data_race);
		printf("%i Philo %i died\n", get_timestamp(philo->data), (philo->id + 1));
		return (philo->data->dead);
	}
	pthread_mutex_unlock(&philo->data->data_race);
	return (philo->data->dead);
}

void	*verify_run(void *philo)
{
	t_philo	*p;
	
	p = ((t_philo *)philo);
	while ((p->data->table.philo_nbr - 1) != p->id || !can_start_run(p->data, p->id))
	{
		if (p->data->time.tv_sec)
			break ;
	}
	p->life = 0 + p->data->table.time_to_die;
	start_run(p);
	return(0);
}

void	*start_run(t_philo *p)
{
	int i = 0;
	while (!is_dead(p))
		i++;
	return (0);
}

void	init_thread(t_data *data)
{
	data->count = 0;
	pthread_mutex_init(&data->data_race, NULL);
	while (data->count < data->table.philo_nbr)
	{
		data->philo[data->count].data = data;
		data->philo[data->count].id = data->count;
		data->philo[data->count].forks = 1;
		data->philo[data->count].times_eated = 0;
		pthread_mutex_init(&data->philo[data->count].mutex, NULL);
		pthread_create(&data->philo[data->count].thread,
			0, &verify_run, (void *)&data->philo[data->count]);
		data->count++;
	}
	while (data->count-- > 0)
		pthread_join(data->philo[data->count].thread, NULL);
	while (++data->count < data->table.philo_nbr)
		pthread_mutex_destroy(&data->philo[data->count].mutex);
}
