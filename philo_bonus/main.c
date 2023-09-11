/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/11 12:02:37 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	create_philos(t_dinner *dinner, int ac, char **av)
{
	dinner->philo_full = 0;
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
	dinner->philo = ft_calloc(dinner->nbr_philos, sizeof(*dinner->philo));
	set_table(dinner);
	dinner->start_time = get_times();
}

void	kill_philos(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nbr_philos)
	{
		kill(dinner->philo[i].pid, SIGTERM);
	}
}

void	fork_philos(t_dinner *dinner)
{
	int	i;
	int pid;

	i = -1;
	pid = -1;
	while (++i < dinner->nbr_philos && pid != 0)
	{
		pid = fork();
		if (pid != 0)
		{
			dinner->philo[i].pid = pid;
		}
	}
	if (pid == 0)
	{
		philo_life(&dinner->philo[1]);
	}
	else
	{
		sem_wait(dinner->end);
		kill_philos(dinner);
	}
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (verify_args(argc, argv))
	{
		return (1);
	}
	create_philos(&dinner, argc, argv);
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/end");
	dinner.print = sem_open("/print", O_CREAT, 0644, 1);
	dinner.end = sem_open("/end", O_CREAT, 0644, 0);
	dinner.forks = sem_open("/forks", O_CREAT, 0644, dinner.nbr_philos);
	fork_philos(&dinner);
	sem_close(dinner.print);
	sem_close(dinner.forks);
	sem_close(dinner.end);
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/end");
	return (0);
}
