/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/03/28 01:45:08 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// #define NBR_THREADS 2

// int	main(int argc, char *argv[])
// {
// 	t_data	data;

// 	if (argc < 5 || argc > 6) 
// 	{
//         printf("Usage: ./philo num_of_philosophers time_to_die time_to_eat time_to_sleep [num_of_times_each_philosopher_must_eat]\n");
//         return 1;
//     }
// 	check_args(&data, argc, argv);
// 	return (0);
// }

// #include <stdio.h>
// #include <pthread.h>

// typedef struct s_test
// {
// 	int				id;
//     int 			error;
// 	struct timeval	time;
//     pthread_t 		threads;
// }			t_test;


// int	get_timestamp2(t_test *test)
// {
// 	struct	timeval	get_time;

// 	gettimeofday(&get_time, NULL);
// 	return ((int) (get_time.tv_sec * 1000 + get_time.tv_usec / 1000)
// 		- (test->time.tv_sec * 1000 +  test->time.tv_usec / 1000));
// }

// void	*thread_func(void *test) 
// {
// 	t_test t;
// 	t = *(t_test*)test;
//     printf("%i Philosopher %d is eating\n", get_timestamp2(&t), t.id);
//     printf("%i Philosopher %d is sleeping\n", get_timestamp2(&t), t.id);
//     printf("%i Philosopher %d is thinking\n", get_timestamp2(&t),t.id);
//     return(0);
// }

// int main() {
// 	int i;
// 	t_test test[NBR_THREADS];
	
//     // Cria as threads
// 	test->time.tv_sec = 0;
// 	// printf("%i\n", get_timestamp2(&test->time));
// 	i = 0;
// 	while (i < NBR_THREADS)
// 	{
// 		gettimeofday(&test[i].time, NULL);
// 		test[i].id = i;
//     	test->error = pthread_create(&test[i].threads, NULL, thread_func, &test[i]);
// 		if (test->error) 
// 		{
// 			printf("Erro: código de retorno de pthread_create() é %d\n", test->error);
// 			return -1;
// 		}
// 		i++;
// 	}
// 	// Aguarda as threads terminarem
// 	i--;
// 	while (i >= 0)
// 	{
// 		test->error = pthread_join(test[i].threads, NULL);
// 		if (test->error)
// 		{
// 			printf("Erro: código de retorno de pthread_join() é %d\n", test->error);
// 			return -1;
// 		}
// 		i--;
// 	}
// 	printf("Todas as threads terminaram.\n");
// 	return 0;
// }

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NBR_THREADS 2

typedef struct s_philo {
    int id;
    pthread_t thread;
} t_philo;

void print_timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long int ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    printf("%ldms ", ms);
}

void *philosopher(void *arg) {
    t_philo philo = *(t_philo *)arg;
    usleep(2000); // Tempo para pensamento
    print_timestamp();
    printf("Philosopher %d is hungry\n", philo.id);
    usleep(2000); // Tempo para comer
    print_timestamp();
    printf("Philosopher %d is sleeping\n", philo.id);
    usleep(2000); // Tempo para dormir
    print_timestamp();
    printf("Philosopher %d is thinking\n", philo.id);
    return NULL;
}

int main(void) {
    t_philo philosophers[NBR_THREADS];
    for (int i = 0; i < NBR_THREADS; i++) {
        philosophers[i].id = i + 1;
        pthread_create(&philosophers[i].thread, NULL, philosopher, &philosophers[i]);
    }
    for (int i = 0; i < NBR_THREADS; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }
    return 0;
}
