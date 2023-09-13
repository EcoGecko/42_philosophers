/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:45:45 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/13 14:06:36 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_time);
	if (get_times() - philo->last_meal >= philo->dinner->time_die)
	{
		death(philo);
		pthread_mutex_unlock(&philo->dinner->mutex_time);
		return (true);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	return (false);
}

bool check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_meals);
	if (philo->nbr_meals == philo->dinner->nbr_eats && !philo->full)
	{
		philo->dinner->philos_full++;
		philo->full = true;
	}
	if (philo->dinner->philos_full == philo->dinner->nbr_philos)
	{
		pthread_mutex_unlock(&philo->dinner->mutex_meals);
		return (true);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_meals);
	return (false);
}

void monitoring(t_dinner *dinner)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < dinner->nbr_philos)
		{
			pthread_mutex_lock(&dinner->mutex_death);
			if (check_death(&dinner->philo[i]))
			{
				dinner->death = true;
			}
			if (check_full(&dinner->philo[i]))
			{
				dinner->end_dinner = true;
			}
			pthread_mutex_unlock(&dinner->mutex_death);
			if (dinner->death || dinner->end_dinner)
			{
				return;
			}
		}
	}
}
