/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/12 16:37:24 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int philos_full = 0;

void	create_philos(t_dinner *dinner, int ac, char **av)
{
	dinner->philos_full = 0;
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
		kill(dinner->philo[i].pid, SIGKILL);
		pthread_detach(dinner->philo[i].monitor);
	}
	free(dinner->philo);
}

void	fork_philos(t_dinner *dinner)
{
	int	i;
	int	pid;
	int flag;

	i = -1;
	pid = -1;
	flag = 0;
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
		philo_life(&dinner->philo[i - 1]);
	}
	else
	{
		// sem_wait(dinner->end);
		while (waitpid(0, NULL, 0) > 0)
		{
			if (WIFEXITED(flag))
			{
				flag = WEXITSTATUS(flag);
			}
			if (flag)
			{
				kill_philos(dinner);
				break ;
			}
			else if (dinner->nbr_eats != -1)
			{
				dinner->philos_full++;
				if (dinner->philos_full >= dinner->nbr_philos)
				{
					kill_philos(dinner);
					break ;
				}
			}
		}
			// kill_philos(dinner);
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
	sem_unlink("/vars");
	dinner.print = sem_open("/print", O_CREAT, 0644, 1);
	dinner.end = sem_open("/end", O_CREAT, 0644, 0);
	dinner.forks = sem_open("/forks", O_CREAT, 0644, dinner.nbr_philos);
	dinner.vars = sem_open("/vars", O_CREAT, 0644, 1);
	fork_philos(&dinner);
	sem_close(dinner.print);
	sem_close(dinner.forks);
	sem_close(dinner.end);
	sem_close(dinner.vars);
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/vars");
	return (0);
}
