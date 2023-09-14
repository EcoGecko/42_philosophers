/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:56:48 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/14 19:28:51 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

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
		dinner->philo[i - 1].last_meal = dinner->start_time;
		dinner->philo[i - 1].full = false;
	}
}

/* Get the time and converts it to milliseconds */
long long	get_times(void)
{
	struct timeval	time;
	long long		times;

	gettimeofday(&time, NULL);
	times = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (times);
}

void create_philos(t_dinner *dinner, int ac, char **av)
{
	dinner->philos_full = 0;
	dinner->nbr_philos = ft_atoll(av[1]);
	dinner->time_die = ft_atoll(av[2]);
	dinner->time_eat = ft_atoll(av[3]);
	dinner->time_sleep = ft_atoll(av[4]);
	if (ac == 6)
	{
		dinner->nbr_eats = ft_atoll(av[5]);
	} else
	{
		dinner->nbr_eats = -1;
	}
	dinner->philo = ft_calloc(dinner->nbr_philos, sizeof(*dinner->philo));
	dinner->start_time = get_times();
	set_table(dinner);
}

void kill_philos(t_dinner *dinner)
{
	int i;

	i = -1;
	while (++i < dinner->nbr_philos)
	{
		kill(dinner->philo[i].pid, SIGKILL);
	}
	free(dinner->philo);
}

void print(t_philo *philo, char *str)
{
	sem_wait(philo->dinner->sem_print);
	printf("%lld %d %s\n", get_times() - philo->dinner->start_time,
		   philo->id, str);
	sem_post(philo->dinner->sem_print);
}
