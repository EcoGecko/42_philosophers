/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:01:20 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/25 14:22:13 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->fork = 1;
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	philo->right_fork->fork = 1;
	philo->last_meal = get_times();
	philo->nbr_eats++;
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	printf("%ld %d is eating\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	usleep(philo->dinner->time_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
}
