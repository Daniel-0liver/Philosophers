/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/06 21:37:35 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6) 
	{
		check_args(argc, argv);
		if (data()->error)
			return (1);
		init_thread();
    }
	else
	{
        printf("Usage: ./philo \n\t%snum_of_philosophers\n", GREEN);
		printf("\ttime_to_die\n\ttime_to_eat\n\ttime_to_sleep%s\n", COLOUR_END);
		printf("Opt: %s   [times_philosopher_must_eat]%s\n", YELLOW, COLOUR_END);
        return (1);
	}
	return (0);
}
