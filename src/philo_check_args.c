/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/04/02 15:20:14 by dateixei         ###   ########.fr       */
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

void	is_non_number(char **argv)
{
	int	j;
	int i;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while ((ft_isdigit(argv[i][j])) == 1 && argv[i][j])
			j++;
		if ((argv[i][0] == '+')
			&& (ft_isdigit(argv[i][j + 1])))
		{
			j++;
			while ((ft_isdigit(argv[i][j]) == 1))
				j++;
		}
		if (argv[i][j] && ft_isdigit(argv[i][j]) == 0)
			data()->error = 1;
		i++;
	}
}

long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\f'))
		i++;
	if (str[i] && str[i] == '-')
	{
		data()->error = 1;
		return (0);
	}
	while (str[i] && (str[i] >= '0' || str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	if (result > 2147483647 || result < -2147483648)
		data()->error = 1;
	return (result);
}

int	check_args(int argc, char **argv)
{
	data()->error = 0;
	is_non_number(argv);
	data()->nbr_philo = ft_atoi(argv[1]);
	data()->times[die]= ft_atoi(argv[2]);
	data()->times[eat] = ft_atoi(argv[3]);
	data()->times[t_sleep] = ft_atoi(argv[4]);
	if (argc == 6)
		data()->times_to_eat = ft_atoi(argv[5]);
	else
		data()->times_to_eat = 0;
	if (data()->error == 1)
		return (printf("%sIt is not a valid number%s\n", RED, COLOUR_END));
	return (0);
}
