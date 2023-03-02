/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/02 14:24:50 by dateixei         ###   ########.fr       */
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