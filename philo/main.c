/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/13 18:09:11 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philos.h"

void	init_struct(t_dinner *dinner, int ac, char **av)
{
	dinner->philos_full = 0;
	dinner->end_dinner = false;
	dinner->death = false;
	dinner->nbr_philos = ft_atol(av[1]);
	dinner->time_die = ft_atol(av[2]);
	dinner->time_eat = ft_atol(av[3]);
	dinner->time_sleep = ft_atol(av[4]);
	if (ac == 6)
	{
		dinner->nbr_eats = ft_atol(av[5]);
	}
	else
	{
		dinner->nbr_eats = -1;
	}
	dinner->fork = ft_calloc(dinner->nbr_philos, sizeof(*dinner->fork));
	dinner->philo = ft_calloc(dinner->nbr_philos, sizeof(*dinner->philo));
	dinner->start_time = get_times();
	set_table(dinner);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->dinner->mutex_death);
		if (philo->dinner->end_dinner || philo->dinner->death)
		{
			pthread_mutex_unlock(&philo->dinner->mutex_death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->dinner->mutex_death);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	clean_all(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nbr_philos)
	{
		pthread_mutex_destroy(&dinner->fork[i].mutex_fork);
	}
	pthread_mutex_destroy(&dinner->mutex_print);
	pthread_mutex_destroy(&dinner->mutex_death);
	pthread_mutex_destroy(&dinner->mutex_meals);
	pthread_mutex_destroy(&dinner->mutex_time);
	free(dinner->fork);
	free(dinner->philo);
}

void	initializer(t_dinner *dinner, int argc, char **argv)
{
	int	i;

	init_struct(dinner, argc, argv);
	pthread_mutex_init(&dinner->mutex_print, NULL);
	pthread_mutex_init(&dinner->mutex_death, NULL);
	pthread_mutex_init(&dinner->mutex_meals, NULL);
	pthread_mutex_init(&dinner->mutex_time, NULL);
	i = -1;
	while (++i < dinner->nbr_philos)
	{
		pthread_mutex_init(&dinner->fork[i].mutex_fork, NULL);
	}
	i = -1;
	while (++i < dinner->nbr_philos)
	{
		pthread_create(&dinner->philo[i].philo, \
		NULL, &routine, &dinner->philo[i]);
	}
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	int			i;

	if (verify_input(argc, argv))
	{
		return (1);
	}
	initializer(&dinner, argc, argv);
	monitoring(&dinner);
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		pthread_join(dinner.philo[i].philo, NULL);
	}
	clean_all(&dinner);
	return (0);
}
