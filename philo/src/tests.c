/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:13:05 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/24 13:15:30 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	print_tester(t_dinner *dinner)
{
	printf("Number of philosophers at the dinner: %d\n", dinner->nbr_philos);
	printf("Time to die: %d\n", dinner->time_die);
	printf("Time to eat: %d\n", dinner->time_eat);
	printf("Time to sleep: %d\n", dinner->time_sleep);
	printf("Number of times each philosopher has to eat: %d\n", dinner->nbr_eats);
	for (int i = 0; i < dinner->nbr_philos; i++)
	{
		printf("Fork %d state is: %d\n", i, dinner->fork[i]);
		printf("Philosopher number %d id is: %d\n", i, dinner->philo[i].id);
	}
}
