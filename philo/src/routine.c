/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:01:20 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/26 20:29:50 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	// philo->right_fork->fork = 1;
	if (philo->dinner->nbr_philos == 1)
	{
		usleep(philo->dinner->time_die * 1000);
		philo->nbr_meals++;
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	// philo->left_fork->fork = 1;
	pthread_mutex_lock(&philo->dinner->mutex_print);
	philo->last_meal = get_times();
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	printf("%ld %d is eating\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	// philo->right_fork->fork = 0;
	// philo->left_fork->fork = 0;
	usleep(philo->dinner->time_eat * 1000);
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d is sleeping\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	usleep(philo->dinner->time_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d is thinking\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_print);
	if (philo->last_meal + philo->dinner->time_die < get_times())
	{
		philo->dinner->end_dinner = 1;
		printf("%ld %d died\n", get_times() - philo->dinner->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_print);
}
