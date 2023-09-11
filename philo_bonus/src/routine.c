/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:47:23 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/01 15:48:43 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	end_dinner(t_philo *philo)
{
	if (get_times() - philo->last_meal > philo->dinner->time_die || philo->nbr_meals == philo->dinner->nbr_eats)
	{
		if (get_times() - philo->last_meal > philo->dinner->time_die)
		{
			printf("%ld %d died\n", get_times() - philo->dinner->start_time, philo->id);
			sem_post(philo->dinner->end);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->dinner->end);
		exit(EXIT_SUCCESS);
	}
}

void	philo_life(t_philo *philo)
{
	while (1)
	{
		// sem_wait(philo->dinner->print);
		sem_wait(philo->dinner->forks);
		printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
		if (philo->dinner->nbr_philos == 1)
		{
			usleep(philo->dinner->time_eat * 1000);
			end_dinner(philo);
		}
		sem_wait(philo->dinner->forks);
		printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
		printf("%ld %d is eating\n", get_times() - philo->dinner->start_time, philo->id);
		philo->last_meal = get_times();
		philo->nbr_meals++;
		// sem_post(philo->dinner->print);
		usleep(philo->dinner->time_eat * 1000);
		sem_post(philo->dinner->forks);
		printf("%ld %d dropped a fork\n", get_times() - philo->dinner->start_time, philo->id);
		sem_post(philo->dinner->forks);
		printf("%ld %d dropped a fork\n", get_times() - philo->dinner->start_time, philo->id);
		if (get_times() - philo->last_meal > philo->dinner->time_die || philo->nbr_meals == philo->dinner->nbr_eats)
		{
			end_dinner(philo);
		}
		printf("%ld %d is sleeping\n", get_times() - philo->dinner->start_time, philo->id);
		usleep(philo->dinner->time_sleep * 1000);
		printf("%ld %d is thinking\n", get_times() - philo->dinner->start_time, philo->id);
	}
	exit(EXIT_SUCCESS);
}
