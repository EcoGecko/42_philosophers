/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:19:53 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/11 16:20:41 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	check_death(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->dinner->mutex_meals);
	pthread_mutex_lock(&philo->dinner->mutex_death);
	if (philo->dinner->end_dinner == 1)
	{
		if (flag)
		{
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		}
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		pthread_mutex_unlock(&philo->dinner->mutex_meals);
		pthread_mutex_unlock(&philo->dinner->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_meals);
	pthread_mutex_unlock(&philo->dinner->mutex_death);
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
	if (philo->dinner->end_dinner == 1)
	{
		return ;
	}
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("%ld %d %s\n", get_times() - philo->dinner->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->dinner->mutex_print);
}
