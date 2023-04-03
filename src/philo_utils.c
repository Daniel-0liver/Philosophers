/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:38:32 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/04 00:38:22 by dateixei         ###   ########.fr       */
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

void	only_one_philo(t_philo	*philo)
{
	print_event(philo->id, eat);
	print_event(philo->id, t_sleep);
	print_event(philo->id, think);
	print_event(philo->id, t_fork);
	print_event(philo->id, die);
}

void	print_event(int id, int cod)
{
	long	cur_time;

	// usleep(data()->times[t_sleep] * 1000);
	cur_time = get_timestamp(data()->start_time);
	pthread_mutex_lock(&data()->mutex.print);
	printf("%s%ldms%s %d ", LGRAY, cur_time, COLOUR_END, id);
	if (cod == 0)
		printf("%sdied%s\n", RED, COLOUR_END);
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