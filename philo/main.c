/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/24 17:40:23 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philos.h"

void	init_struct(t_dinner *dinner, int ac, char *av[])
{
	int	i;

	dinner->nbr_philos = ft_atol(av[1]);
	dinner->time_die = ft_atol(av[2]);
	dinner->time_eat = ft_atol(av[3]);
	dinner->time_sleep = ft_atol(av[4]);
	if (ac == 6)
		dinner->nbr_eats = ft_atol(av[5]);
	else
		dinner->nbr_eats = -1;
	dinner->fork = ft_calloc(dinner->nbr_philos, sizeof(*dinner->fork));
	dinner->philo = ft_calloc(dinner->nbr_philos, sizeof(*dinner->philo));
	i = 0;
	while (++i <= dinner->nbr_philos)
	{
		dinner->philo[i - 1].id = i;
	}
	dinner->start_time = get_times();
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo[%d] is eating\n", philo->id); //TMP - just to see
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
	return (0);
}
