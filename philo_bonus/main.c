/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/15 12:09:34 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	end_dinner(t_dinner *dinner)
{
	int	i;

	i = dinner->nbr_philos;
	while (i--)
	{
		sem_wait(dinner->sem_end);
	}
	kill_philos(dinner);
}

void	fork_philos(t_dinner *dinner)
{
	int	i;
	int	pid;

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
		philo_life(&dinner->philo[i - 1]);
	}
	else
	{
		end_dinner(dinner);
	}
}

void	open_sems(t_dinner *dinner)
{
	sem_unlink("/print");
	sem_unlink("/time");
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/eat");
	dinner->sem_print = sem_open("/print", O_CREAT, 0644, 1);
	dinner->sem_time = sem_open("/time", O_CREAT, 0644, 1);
	dinner->sem_end = sem_open("/end", O_CREAT, 0644, 0);
	dinner->sem_forks = sem_open("/forks", O_CREAT, 0644, dinner->nbr_philos);
	dinner->sem_eat = sem_open("/eat", O_CREAT, 0644, dinner->nbr_philos / 2);
}

void	close_sems(t_dinner *dinner)
{
	sem_close(dinner->sem_print);
	sem_close(dinner->sem_time);
	sem_close(dinner->sem_end);
	sem_close(dinner->sem_forks);
	sem_close(dinner->sem_eat);
	sem_unlink("/print");
	sem_unlink("/time");
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/eat");
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (verify_args(argc, argv))
	{
		return (1);
	}
	create_philos(&dinner, argc, argv);
	open_sems(&dinner);
	fork_philos(&dinner);
	close_sems(&dinner);
	return (0);
}
