/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:01:20 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/14 19:28:02 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	print(philo, FORK);
	if (philo->dinner->nbr_philos == 1)
	{
		usleep(philo->dinner->time_die * 1000);
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	print(philo, FORK);
	print(philo, EAT);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal = get_times();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	usleep(philo->dinner->time_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->dinner->mutex_meals);
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->dinner->mutex_meals);
}

void	sleeping(t_philo *philo)
{
	print(philo, SLEEP);
	usleep(philo->dinner->time_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	long	think_time;

	think_time = philo->dinner->time_die - \
	(philo->dinner->time_eat + philo->dinner->time_sleep) / 2;
	usleep(think_time);
	print(philo, THINK);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d died\n", get_times() - philo->dinner->start_time, \
	philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
}
