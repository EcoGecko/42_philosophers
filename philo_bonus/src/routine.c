/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:23 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/14 19:28:35 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	check_death(t_philo *philo)
{
	int i;
	long long time = get_times();

	sem_wait(philo->dinner->sem_time);
	if (time - philo->last_meal >= philo->dinner->time_die)
	{
		sem_post(philo->dinner->sem_time);
		print(philo, "died");
		i = -1;
		while (++i < philo->dinner->nbr_philos)
		{
			sem_post(philo->dinner->sem_end);
		}
		printf("%d %d\n", i, philo->id);
		return (true);
	}
	sem_post(philo->dinner->sem_time);
	return (false);
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (check_death(philo))
		{
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->dinner->sem_eat);
	sem_wait(philo->dinner->sem_forks);
	print(philo, FORK);
	sem_wait(philo->dinner->sem_forks);
	print(philo, FORK);
	print(philo, EAT);
	sem_post(philo->dinner->sem_eat);
	sem_wait(philo->dinner->sem_time);
	philo->last_meal = get_times();
	sem_post(philo->dinner->sem_time);
	sem_wait(philo->dinner->sem_time);
	philo->nbr_meals++;
	sem_post(philo->dinner->sem_time);
	usleep(philo->dinner->time_eat * 1000);
	sem_post(philo->dinner->sem_forks);
	sem_post(philo->dinner->sem_forks);
	if (philo->nbr_meals == philo->dinner->nbr_eats)
	{
		sem_post(philo->dinner->sem_end);
	}
}

void	philo_life(t_philo *philo)
{
	philo->last_meal = philo->dinner->start_time;
	pthread_create(&philo->monitor, NULL, &monitoring, philo);
	while (1)
	{
		eat(philo);
		print(philo, SLEEP);
		usleep(philo->dinner->time_sleep * 1000);
		usleep(philo->dinner->time_die - \
		(philo->dinner->time_eat + philo->dinner->time_sleep) / 2);
		print(philo, THINK);
	}
}
