/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/25 02:23:05 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_args(t_data *data, int argc, char **argv)
{
	data->table.error = 0;
	is_non_number(argv, data);
	if (data->table.error == 1)
		return ;
	data->table.philo_nbr = ft_atoi(argv[1], data);
	data->table.time_to_die = ft_atoi(argv[2], data);
	data->table.time_to_eat = ft_atoi(argv[3], data);
	data->table.time_to_sleep = ft_atoi(argv[4], data);
	if (argc == 6)
		data->table.nbr_to_eat = ft_atoi(argv[5], data);
	else
		data->table.nbr_to_eat = 2147483647;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	
	gettimeofday(&data.time, NULL);
	if (argc < 5 || argc > 6) 
	{
        printf("Usage: ./philo num_of_philosophers time_to_die time_to_eat time_to_sleep [num_of_times_each_philosopher_must_eat]\n");
        return 1;
    }
	check_args(&data, argc, argv);
	return (0);
}

// #include <stdio.h>
// #include <pthread.h>

// #define NUM_THREADS 10

// void* thread_func(void* arg) {
//     int thread_id = *((int*) arg);
//     printf("Thread %d está em execução.\n", thread_id);
//     // Fazer algo útil aqui
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     int thread_args[NUM_THREADS];
//     int rc, i;

//     // Cria as threads
//     for (i = 0; i < NUM_THREADS; i++) {
//         thread_args[i] = i;
// 		printf("%p\n", &thread_args[i]);
//         rc = pthread_create(&threads[i], NULL, thread_func, (void*) &thread_args[i]);
//         if (rc) {
//             printf("Erro: código de retorno de pthread_create() é %d\n", rc);
//             return -1;
//         }
//     }

//     // Aguarda as threads terminarem
//     for (i = 0; i < NUM_THREADS; i++) {
//         rc = pthread_join(threads[i], NULL);
//         if (rc) {
//             printf("Erro: código de retorno de pthread_join() é %d\n", rc);
//             return -1;
//         }
//     }

//     printf("Todas as threads terminaram.\n");
//     return 0;
// }
