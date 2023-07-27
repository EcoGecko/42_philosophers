/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:01:20 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/27 20:21:45 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	if (check_death(philo, 0))
	{
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	if (philo->dinner->nbr_philos == 1)
	{
		usleep(philo->dinner->time_die * 1000);
		death(philo);
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		return ;
	} 
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	if (check_death(philo, 1))
	{
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d has taken a fork\n", get_times() - philo->dinner->start_time, philo->id);
	printf("%ld %d is eating\n", get_times() - philo->dinner->start_time, philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	philo->last_meal = get_times();
	philo->nbr_meals++;
	usleep(philo->dinner->time_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);

}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_meals);
	pthread_mutex_lock(&philo->dinner->mutex_death);
	if (philo->dinner->end_dinner == 1)
	{
		pthread_mutex_unlock(&philo->dinner->mutex_death);
		pthread_mutex_unlock(&philo->dinner->mutex_meals);
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d is sleeping\n", get_times() - philo->dinner->start_time, \
	philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_unlock(&philo->dinner->mutex_death);
	pthread_mutex_unlock(&philo->dinner->mutex_meals);
	usleep(philo->dinner->time_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_meals);
	pthread_mutex_lock(&philo->dinner->mutex_death);
	if (philo->dinner->end_dinner == 1)
	{
		pthread_mutex_unlock(&philo->dinner->mutex_death);
		pthread_mutex_unlock(&philo->dinner->mutex_meals);
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d is thinking\n", get_times() - philo->dinner->start_time, \
	philo->id);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_unlock(&philo->dinner->mutex_death);
	pthread_mutex_unlock(&philo->dinner->mutex_meals);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_death);
	if (philo->last_meal + philo->dinner->time_die < get_times())
	{
		if (philo->dinner->end_dinner == 1)
		{
			pthread_mutex_unlock(&philo->dinner->mutex_death);
			return ;
		}
		philo->dinner->end_dinner = 1;
		pthread_mutex_lock(&philo->dinner->mutex_print);
		printf("%ld %d died\n", get_times() - philo->dinner->start_time, \
		philo->id);
		pthread_mutex_unlock(&philo->dinner->mutex_print);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_death);
}
