/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/27 21:02:43 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void	is_non_number(char **argv, t_data *data)
{
	int	j;
	int i;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while ((ft_isdigit(argv[i][j])) == 1 && argv[i][j])
			j++;
		if ((argv[i][j] == '-' || argv[i][j] == '+')
			&& (ft_isdigit(argv[i][j + 1])))
		{
			j++;
			while ((ft_isdigit(argv[i][j]) == 1))
				j++;
		}
		if (argv[i][j] && ft_isdigit(argv[i][j]) == 0)
			data->table.error = 1;
		i++;
	}
}

int	ft_atoi(char *str, t_data *data)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\f'))
		i++;
	if (str[i] && str[i] == '-')
	{
		data->table.error = 1;
		return (0);
	}
	while (str[i] && (str[i] >= '0' || str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	if (result > 2147483647 || result < -2147483648)
		data->table.error = 1;
	return (result);
}

int	get_timestamp(t_data *data)
{
	struct	timeval	get_time;

	gettimeofday(&get_time, NULL);
	return ((int) (get_time.tv_sec * 1000 + get_time.tv_usec / 1000)
		- (data->time.tv_sec * 1000 +  data->time.tv_usec / 1000));
}

void	check_args(t_data *data, int argc, char **argv)
{
	data->table.error = 0;
	is_non_number(argv, data);
	data->table.philo_nbr = ft_atoi(argv[1], data);
	data->table.time_to_die = ft_atoi(argv[2], data);
	data->table.time_to_eat = ft_atoi(argv[3], data);
	data->table.time_to_sleep = ft_atoi(argv[4], data);
	if (data->table.error == 1)
	{
		printf("Some argument isn't a positive number, try again!\n");
		return ;
	}
	data->is_running = 0;
	data->dead = 0;
	data->time.tv_sec = 0;
	if (argc == 6)
		data->table.nbr_to_eat = ft_atoi(argv[5], data);
	else
		data->table.nbr_to_eat = 2147483647;
	data->philo = malloc(sizeof(t_philo) * data->table.philo_nbr);
	if (!data->philo && printf("Allocate memory failed\n"))
		return ;
	init_thread(data);
}