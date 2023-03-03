/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/03 23:31:38 by dateixei         ###   ########.fr       */
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

void	is_non_number(char **argv, t_stacks *stack)
{
	int	j;

	stack->i = 1;
	while (argv[stack->i])
	{
		j = 0;
		while ((ft_isdigit(argv[stack->i][j])) == 1 && argv[stack->i][j])
			j++;
		if ((argv[stack->i][j] == '-' || argv[stack->i][j] == '+')
			&& (ft_isdigit(argv[stack->i][j + 1])))
		{
			j++;
			while ((ft_isdigit(argv[stack->i][j]) == 1))
				j++;
		}
		if (argv[stack->i][j] && ft_isdigit(argv[stack->i][j]) == 0)
		{
			free(stack->stack_a);
			stack->stack_a = NULL;
			write(STDERR_FILENO, "Error\n", 6);
			exit(-1);
		}
		stack->i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	sig;
	int	result;

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
	return (result * sig);
}