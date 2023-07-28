/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/28 22:09:29 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	int			i;
	int			flag;

	if (verify_args(argc, argv))
	{
		return (1);
	}
	//create_philos
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		dinner.philos[i].pid = fork();
		if (dinner.philos[i].pid == 0)
		{
			philo_life(&dinner.philos[i]);
		}
	}
	waitpid(0, NULL, &flag);
	if (WIFEXITED(flag))
	{
		flag = WEXITSTATUS(flag);
	}
	i = -1;
	while (++i < dinner.nbr_philos)
	{
		kill(dinner.philos[i].pid, SIGKILL);
	}
	return (0);
}
