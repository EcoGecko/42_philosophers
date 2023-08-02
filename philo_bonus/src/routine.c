/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:23 by heda-sil          #+#    #+#             */
/*   Updated: 2023/08/02 18:14:16 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	philo_life(t_philo *philo)
{
	while (1)
	{
		// if (philo->id % 2 == 0)
		// {
		// 	usleep(100);
		// }
		sem_wait(philo->dinner->print);
		sem_wait(philo->dinner->forks);
		printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
		sem_wait(philo->dinner->forks);
		printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
		printf("%ld %d is eating\n", get_times() - philo->dinner->start_time, philo->id);
		philo->last_meal = get_times();
		usleep(philo->dinner->time_eat * 1000);
		sem_post(philo->dinner->forks);
		printf("%ld %d dropped a fork\n", get_times() - philo->dinner->start_time, philo->id);
		sem_post(philo->dinner->forks);
		printf("%ld %d dropped a fork\n", get_times() - philo->dinner->start_time, philo->id);
		printf("philo_life %d\n", philo->id);
		sem_post(philo->dinner->print);
		printf("%ld %d is sleeping\n", get_times() - philo->dinner->start_time, philo->id);
		usleep(philo->dinner->time_sleep * 1000);
		printf("%ld %d is thinking\n", get_times() - philo->dinner->start_time, philo->id);
		if (philo->last_meal + philo->dinner->time_die < get_times())
		{
			sem_wait(philo->dinner->print);
			printf("%ld %d died\n", get_times() - philo->dinner->start_time, philo->id);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
