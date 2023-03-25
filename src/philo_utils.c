/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/25 02:22:15 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	int		sig;
	long	result;

	i = 0;
	sig = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\f'))
		i++;
	if (str[i] && str[i] == '-')
	{
		sig = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' || str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	if (result > 2147483647 || result < -2147483648)
		data->table.error = 1;
	return (result * sig);
}

int	get_timestamp(t_data *data)
{
	struct	timeval	get_time;
	gettimeofday(&get_time, NULL);
	return ((int) (get_time.tv_sec * 1000 + get_time.tv_usec / 1000)
		- (data->time.tv_sec * 1000 +  data->time.tv_usec / 1000));
}

