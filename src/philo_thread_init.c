/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:52:16 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/29 20:56:04 by dateixei         ###   ########.fr       */
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
	pthread_mutex_lock(&p->data->data_race);
	printf("%i Philo: %d\n", get_timestamp(p->data), p->id);
	usleep(100000);
	printf("%i Philo: %d\n", get_timestamp(p->data), p->id);
	usleep(100000);
	printf("%i Philo: %d\n", get_timestamp(p->data), p->id);
	pthread_mutex_unlock(&p->data->data_race);
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
