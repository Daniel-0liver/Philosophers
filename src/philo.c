/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/11 21:06:01 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_args(t_philo *philo, int argc, char **argv)
{
	is_non_number(argv, philo);
	if (philo->error == 1)
		return ;
	philo->philo_nbr = ft_atoi(argv[1], philo);
	philo->time_to_die = ft_atoi(argv[2], philo);
	philo->time_to_eat = ft_atoi(argv[3], philo);
	philo->time_to_sleep = ft_atoi(argv[4], philo);
	if (argc == 6)
		philo->nbr_to_eat = ft_atoi(argv[5], philo);
	else
		philo->nbr_to_eat = 2147483647;
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
		
	gettimeofday(&philo.time, NULL);
	if (argc < 5 || argc > 6) 
	{
        printf("Usage: ./philo num_of_philosophers time_to_die time_to_eat time_to_sleep [num_of_times_each_philosopher_must_eat]\n");
        return 1;
    }
	check_args(&philo, argc, argv);
	for (size_t i = 0; i < 10; i++)
	{
		printf("%i\n", get_timestamp(&philo));
	}
	return (0);
}
