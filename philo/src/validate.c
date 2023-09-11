/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:57:12 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/11 15:44:11 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
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
	int			i;
	long int	arg;

	i = 0;
	while (args[++i])
	{
		if (!is_number(args[i]))
		{
			printf("Error: The %d argument is not a valid number\n", i);
			return (1);
		}
		arg = ft_atol(args[i]);
		if (arg <= 0 || (arg > INT_MAX))
		{
			printf("Error: All arguments should be positive \
and bellow int max\n");
			return (1);
		}
	}
	return (0);
}

int	verify_input(int argc, char **argv)
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
