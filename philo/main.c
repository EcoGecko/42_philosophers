/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:35:43 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/24 14:35:50 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philos.h"

void	init_struct(t_dinner *dinner, int ac, char *av[])
{
	int	i;

	dinner->nbr_philos = ft_atoi(av[1]);
	dinner->time_die = ft_atoi(av[2]);
	dinner->time_eat = ft_atoi(av[3]);
	dinner->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dinner->nbr_eats = ft_atoi(av[5]);
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

int	is_digit(char arg)
{
	if (arg < '0' || arg > '9')
	{
		return (0);
	}
	return (1);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '-')
	{
		i++;
	}
	while (arg[i])
	{
		if (!is_digit(arg[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_args(char **args)
{
	int	i;
	int	arg;

	i = 0;
	while (args[++i])
	{
		if (!is_number(args[i]))
		{
			printf("Error: The %d argument is not a valid number\n", i);
			return (1);
		}
		arg = ft_atoi(args[i]);
		if (arg < 0)
		{
			printf("Error: All arguments should be positive\n");
			return (1);
		}
	}
	return (0);
}

int	verify_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	else if (validate_args(argv))
	{
		printf("Run as: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> and optionally <minimum_times_to_eat>\n");
		return (1);
	}
	return (0);
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
