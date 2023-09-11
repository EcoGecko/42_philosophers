/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:23 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/11 12:38:22 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*end_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (get_times() - philo->last_meal > philo->dinner->time_die)
		{
			sem_wait(philo->dinner->print);
			printf("%ld %d died\n", get_times() - philo->dinner->start_time, philo->id);
			sem_post(philo->dinner->end);
		}
		if (philo->nbr_meals == philo->dinner->nbr_eats)
		{
			sem_post(philo->dinner->end);
		}
	}
	return (0);
}

void	print(t_philo *philo, char *str)
{
	sem_wait(philo->dinner->print);
	printf("%ld %d %s\n", get_times() - philo->dinner->start_time, philo->id, str);
	sem_post(philo->dinner->print);
}

void	philo_life(t_philo *philo)
{
	pthread_t	monitor;

	philo->last_meal = philo->dinner->start_time;
	pthread_create(&monitor, NULL, end_dinner, philo);
	while (1)
	{
		print(philo, THINK);
		sem_wait(philo->dinner->forks);
		print(philo, FORK);
		sem_wait(philo->dinner->forks);
		print(philo, FORK);
		print(philo, EAT);
		philo->last_meal = get_times();
		philo->nbr_meals++;
		usleep(philo->dinner->time_eat * 1000);
		sem_post(philo->dinner->forks);
		sem_post(philo->dinner->forks);
		print(philo, SLEEP);
		usleep(philo->dinner->time_sleep * 1000);
	}
	exit(EXIT_SUCCESS);
}
