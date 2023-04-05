/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:38:32 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/05 23:01:00 by dateixei         ###   ########.fr       */
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
	if (cod == 1)
		printf("%sis eating%s\n", GREEN, COLOUR_END);
	else if (cod == 2)
		printf("%sis sleeping%s\n", YELLOW, COLOUR_END);
	else if (cod == 3)
		printf("%sis thinking%s\n", YELLOW, COLOUR_END);
	else if (cod == 4)
		printf("%shas taken a fork%s\n", GREEN, COLOUR_END);
	pthread_mutex_unlock(&data()->mutex.print);
}

void	print_died(int id)
{
	long	cur_time;

	cur_time = get_timestamp(data()->start_time);
	printf("%s%ldms%s %d ", LGRAY, cur_time, COLOUR_END, id);
	printf("%sdied%s\n", RED, COLOUR_END);
	data()->ev_alive = FALSE;
	pthread_mutex_unlock(&data()->mutex.print);
}