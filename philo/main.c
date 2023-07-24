/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/24 16:12:45 by heda-sil         ###   ########.fr       */
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
		dinner->philo[i - 1].id = i;
	dinner->mutex_fork = ft_calloc(dinner->nbr_philos, sizeof(pthread_mutex_t));
	dinner->start_time = get_times();
}

void	*routine(void *arg)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)arg;
	printf("philo[%d] is eating\n", dinner->philo->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (verify_input(argc, argv))
	{
		return (1);
	}
	else
	{
		init_struct(&dinner, argc, argv);
	}
	print_tester(&dinner);
	return (0);
}
