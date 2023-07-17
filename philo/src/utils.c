/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:35:21 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/17 16:35:21 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*array;

	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero (array, nmemb * size);
	return (array);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
