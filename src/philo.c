/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/27 02:39:18 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	can_start_run(t_data *data, int id)
{
	pthread_mutex_lock(&data->data_race);
	if (id == data->table.philo_nbr - 1)
	{
		gettimeofday(&data->time, NULL);
		data->is_running = 1;
	}
	return (data->is_running);
}

void	*start_run(void *philo)
{
	t_philo	*p;
	
	p = ((t_philo *)philo);
	while ((p->data->table.philo_nbr - 1) != p->id || can_start_run(p->data, p->id))
	{
		if (p->data->time.tv_sec)
			break ;
	}
	p->life = 0 + p->data->table.time_to_die;
	
	return(0);
}

void	init_thread(t_data *data)
{
	data->count = 0;
	pthread_mutex_init(&data->data_race, NULL);
	printf("%d here\n", data->table.philo_nbr);
	while (data->count < data->table.philo_nbr)
	{
		data->philo[data->count].data = data;
		data->philo[data->count].id = data->count;
		data->philo[data->count].forks = 1;
		puts("Worked\n");
		data->philo[data->count].times_eated = 0;
		pthread_mutex_init(&data->philo[data->count].mutex, NULL);
		pthread_create(&data->philo[data->count].thread, 0, &start_run, (void *)&data->philo[data->count]);
		data->count++;
	}
	while (data->count >= 0)
	{
		pthread_join(data->philo[data->count].thread, NULL);
		data->count--;
	}
	while (data->count < data->table.philo_nbr)
	{
		pthread_mutex_destroy(&data->philo[data->count].mutex);
		data->count++;
	}
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

int	main(int argc, char *argv[])
{
	t_data	data;

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
