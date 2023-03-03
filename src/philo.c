/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/03 23:31:28 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6) 
	{
        printf("Usage: ./philo num_of_philosophers time_to_die time_to_eat time_to_sleep [num_of_times_each_philosopher_must_eat]\n");
        return 1;
    }
	printf("%d\n", i);
	return (0);
}
