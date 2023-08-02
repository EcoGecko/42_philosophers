/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_procs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:11:01 by heda-sil          #+#    #+#             */
/*   Updated: 2023/08/02 14:09:45 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PHILO 3

int	main(void)
{
	int		i;
	int		pid;
	sem_t	*forks;

	forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, PHILO);
	if (!forks)
	{
		perror("forks");
		return (1);
	}

	for (i = 0; i < PHILO; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			sem_wait(forks);
			printf("Philosopher %d has taken a fork\n", i);
			sem_wait(forks);
			printf("Philosopher %d has taken a fork\n", i);
			printf("Philosopher %d is eating\n", i);
			sleep(1);
			sem_post(forks);
			printf("Philosopher %d has put down a fork\n", i);
			sem_post(forks);
			printf("Philosopher %d has put down a fork\n", i);
			exit(0);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (1);
		}
	}
	printf("Waiting for philosophers to finish\n");
	for (i = 0; i < PHILO; i++)
		wait(NULL);
//	forks = sem_open("/forks", 0);
	sem_close(forks);
	sem_unlink("/forks");
	return (0);
}
