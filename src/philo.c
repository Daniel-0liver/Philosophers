/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 23:26:09 by dateixei          #+#    #+#             */
/*   Updated: 2023/02/19 01:15:08 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t forks[NUM_PHILOSOPHERS];
int num_meals;
int time_to_wait;

void *philosopher(void *arg) {
    int id = *(int *) arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    int meals_eaten = 0;

    while (meals_eaten < num_meals) {
        // Think for a bit
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 3);

        // Pick up left fork
        sem_wait(&forks[left_fork]);
        printf("Philosopher %d picked up fork %d.\n", id, left_fork);

        // Pick up right fork
        sem_wait(&forks[right_fork]);
        printf("Philosopher %d picked up fork %d.\n", id, right_fork);

        // Eat for a bit
        printf("Philosopher %d is eating.\n", id);
        meals_eaten++;
        sleep(time_to_wait);

        // Put down right fork
        sem_post(&forks[right_fork]);
        printf("Philosopher %d put down fork %d.\n", id, right_fork);

        // Put down left fork
        sem_post(&forks[left_fork]);
        printf("Philosopher %d put down fork %d.\n", id, left_fork);
    }

    printf("Philosopher %d is done eating.\n", id);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_meals> <time_to_wait>\n", argv[0]);
        exit(1);
    }

    // Convert arguments to integers
    int num_meals, time_to_wait;
    if (sscanf(argv[1], "%d", &num_meals) != 1 || sscanf(argv[2], "%d", &time_to_wait) != 1) {
        fprintf(stderr, "Invalid arguments: %s, %s\n", argv[1], argv[2]);
        exit(1);
    }

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&philosophers[i], NULL, philosopher, arg);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}