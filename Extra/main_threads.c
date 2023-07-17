/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:21:35 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/17 11:57:58 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS 80

typedef struct s_philo
{
	int				i;
}	t_philo;

typedef struct s_main
{
	t_philo			*philo;
	pthread_mutex_t	mutex;
	int				idx;
}	t_main;


void	*routine(void *arg)
{
	t_main	*main;

	main = (t_main *)arg;
	pthread_mutex_lock(&main->mutex);
	for (int i = 0; i < 10000000; i++)
		main->idx++;
	pthread_mutex_unlock(&main->mutex);
	printf("PHILO %d is here\n", main->idx);
}

int	main(void)
{
	pthread_t		th[THREADS];
	int				j;
	t_main			main;

	main.idx = 0;
	main.philo = calloc(THREADS, sizeof(*main.philo));
	j = -1;
	pthread_mutex_init(&main.mutex, NULL);
	while (++j < THREADS)
	{
		main.philo[j].i = j + 1;
		pthread_create(th + j, NULL, &routine, &main);
	}
	j = -1;
	while (++j < THREADS)
	{
		pthread_join(th[j], NULL);
	}
	pthread_mutex_destroy(&main.mutex);
	return (0);
}
