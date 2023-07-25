/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/25 14:07:07 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philos.h"

void	set_table(t_dinner *dinner, int nbr_philos)
{
	int	i;

	i = 0;
	while (++i <= dinner->nbr_philos)
	{
		dinner->philo[i - 1].id = i;
		if (i == 1)
		{
			dinner->philo[i - 1].left_fork = &dinner->fork[nbr_philos - 1];
		}
		else
		{
			dinner->philo[i - 1].left_fork = &dinner->fork[i - 1];
		}
		if (i == nbr_philos)
		{
			dinner->philo[i - 1].right_fork = &dinner->fork[0];
		}
		else
		{
			dinner->philo[i - 1].right_fork = &dinner->fork[i];
		}
		dinner->philo[i - 1].dinner = dinner;
	}
}

void	init_struct(t_dinner *dinner, int ac, char **av)
{
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
	set_table(dinner, dinner->nbr_philos);
	dinner->start_time = get_times();
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	eat(philo);
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->fork = 0;
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("philo[%d] has dropped a fork\n", philo->id); //TMP - just to see
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	philo->right_fork->fork = 0;
	pthread_mutex_lock(&philo->dinner->mutex_print);
	printf("philo[%d] has dropped a fork\n", philo->id); //TMP - just to see
	pthread_mutex_unlock(&philo->dinner->mutex_print);
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	int			i;

	if (verify_input(argc, argv))
	{
		return (1);
	}
	else
	{
		init_struct(&dinner, argc, argv);
	}
	print_tester(&dinner);
	pthread_mutex_init(&dinner.mutex_print, NULL);
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		pthread_mutex_init(&dinner.fork[i].mutex_fork, NULL);
	}
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		pthread_create(&dinner.philo[i].philo, NULL, &routine, &dinner.philo[i]);
	}
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		pthread_join(dinner.philo[i].philo, NULL);
	}
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		pthread_mutex_destroy(&dinner.fork[i].mutex_fork);
	}
	pthread_mutex_destroy(&dinner.mutex_print);
	return (0);
}
