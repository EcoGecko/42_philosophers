/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/08/02 18:16:59 by heda-sil         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	int			i;
	int			flag;

	if (verify_args(argc, argv))
	{
		return (1);
	}
	create_philos(&dinner, argc, argv);
	dinner.print = sem_open("/print", O_CREAT, 0644, 1);
	dinner.forks = sem_open("/forks", O_CREAT, 0644, dinner.nbr_philos);
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		dinner.philo[i].pid = fork();
		if (dinner.philo[i].pid == 0)
		{
			// dinner.print = sem_open("/print", O_CREAT, 0644, 1);
			philo_life(&dinner.philo[i]);
		}
	}
	// while (waitpid(0, &flag, 0) > 0)
	// {
	// 	if (WIFEXITED(flag))
	// 	{
	// 		flag = WEXITSTATUS(flag);
	// 	}
	// }
	waitpid(0, &flag, 0);
	// sem_wait(dinner.print);
	if (WIFEXITED(flag))
	{
		flag = WEXITSTATUS(flag);
	}
	i = -1;
	sem_close(dinner.print);
	sem_close(dinner.forks);
	sem_unlink("/print");
	sem_unlink("/forks");
	while (++i < dinner.nbr_philos)
	{
		kill(dinner.philo[i].pid, SIGKILL);
		// sem_post(dinner.print);
	}
	// sem_post(dinner.print);
	// sem_close(dinner.print);
	// sem_close(dinner.forks);
	// sem_unlink("/print");
	// sem_unlink("/forks");
	return (0);
}
