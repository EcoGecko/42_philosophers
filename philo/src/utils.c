/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:19:53 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/12 17:05:56 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_time);
	if (get_times() - philo->last_meal >= philo->dinner->time_die)
	{
		philo->died = true;
		death(philo);
		pthread_mutex_unlock(&philo->dinner->mutex_time);
		return (1);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	return (0);
}

void	set_odd_forks(t_dinner *dinner, int i)
{
	if (i == dinner->nbr_philos)
	{
		dinner->philo[i - 1].left_fork = &dinner->fork[i - 1];
		dinner->philo[i - 1].right_fork = &dinner->fork[0];
	}
	else
	{
		dinner->philo[i - 1].left_fork = &dinner->fork[i - 1];
		dinner->philo[i - 1].right_fork = &dinner->fork[i];
	}
}

void	set_even_forks(t_dinner *dinner, int i)
{
	if (i == dinner->nbr_philos)
	{
		dinner->philo[i - 1].left_fork = &dinner->fork[0];
		dinner->philo[i - 1].right_fork = &dinner->fork[i - 1];
	}
	else
	{
		dinner->philo[i - 1].left_fork = &dinner->fork[i];
		dinner->philo[i - 1].right_fork = &dinner->fork[i - 1];
	}
}

void	set_table(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (++i <= dinner->nbr_philos)
	{
		dinner->philo[i - 1].id = i;
		dinner->philo[i - 1].dinner = dinner;
		dinner->philo[i - 1].nbr_meals = 0;
		dinner->philo[i - 1].last_meal = dinner->start_time;
		dinner->philo[i - 1].died = false;
		dinner->philo[i - 1].full = false;
		if (i % 2 == 0)
		{
			set_even_forks(dinner, i);
		}
		else
		{
			set_odd_forks(dinner, i);
		}
	}
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d %s\n", get_times() - philo->dinner->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
}
