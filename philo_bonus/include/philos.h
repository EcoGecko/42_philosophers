/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/28 22:08:43 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOS_H
# define PHILOS_H

# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	int		nbr_meals;
	long	last_meal;
}	t_philo;

typedef struct	s_dinner
{
	int		nbr_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nbr_eats;
	int		philo_full;
	long	start_time;
	int		nbr_forks;
	t_philo	*philos;
}	t_dinner;

//VALIDATE
int			is_number(char *arg);
int			validate_args(char **args);
int			verify_input(int argc, char **argv);

//LIBFT
long int	ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_digit(char c);

#endif
