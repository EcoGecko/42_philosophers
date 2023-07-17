/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/17 22:15:00 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/* Philo struct where I save all the philo specific information, may need to
 * tweak it a bit
 * => id - philo id
 * => last_meal - time of the last meal used to calculate times
 * => nbr_eats - number of times the philo has eaten if this is equal to the
 * minimal number of meals per philo then the philo stops eating and the program
 * stops
 * */
typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			nbr_eats;
	pthread_t	philo;
}	t_philo;

/* Main struct where I store all dinner related information including the input
 * timming, minimal nbr of meals per philo, nbr of forks on the table etc;
 * TODO - maybe need to add some more vars here such as nbr of philos that have
 * finished all their meals so i know when to stop; maybe i need to change the
 * times fot longs cause of get_times function; */
typedef struct s_dinner
{
	int				nbr_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eats;
	int				start_time;
	int				*fork;
	t_philo			*philo;
	pthread_mutex_t	*mutex_fork;
}	t_dinner;

//UTILS
void	init_struct(t_dinner *dinner, int ac, char *av[]);

//TIMES
long	get_times(void);

//LIBFT
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

//TESTS
void	print_tester(t_dinner *dinner);
#endif
