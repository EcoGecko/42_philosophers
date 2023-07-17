/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/17 14:35:43 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include <stdio.h>

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

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	else
		init_struct(&dinner, argc, argv);
	print_tester(&dinner);
	return (0);
}
