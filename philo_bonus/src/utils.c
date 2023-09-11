/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:56:48 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/01 15:10:16 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/* void	set_odd_forks(t_dinner *dinner, int i)
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
} */

void	set_table(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (++i <= dinner->nbr_philos)
	{
		dinner->philo[i - 1].pid = -1;
		dinner->philo[i - 1].id = i;
		dinner->philo[i - 1].dinner = dinner;
		dinner->philo[i - 1].nbr_meals = 0;
		// if (i % 2 == 0)
		// {
		// 	set_even_forks(dinner, i);
		// }
		// else
		// {
		// 	set_odd_forks(dinner, i);
		// }
	}
}

/* Get the time and converts it to milliseconds */
long	get_times(void)
{
	struct timeval	time;
	long			times;

	gettimeofday(&time, NULL);
	times = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (times);
}
