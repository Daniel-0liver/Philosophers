/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/01/08 23:52:13 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void*	routine()
{
	printf("Hello world\n");
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_join(t1, NULL);

	return (0);
}
