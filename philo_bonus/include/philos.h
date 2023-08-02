/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/08/02 14:12:01 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOS_H
# define PHILOS_H

# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pid_t	pid;
	int		id;
	int		nbr_meals;
	long	last_meal;
	t_dinner	*dinner;
}	t_philo;

typedef struct s_dinner
{
	int		nbr_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nbr_eats;
	int		philo_full;
	long	start_time;
	int		nbr_forks;
	t_philo	*philo;
	sem_t	*print;
	sem_t	*forks;
}	t_dinner;

//VALIDATE
int			is_number(char *arg);
int			validate_args(char **args);
int			verify_args(int argc, char **argv);

//ROUTINE
void	philo_life(t_philo *philo);

//UTILS
long	get_times(void);
void	set_table(t_dinner *dinner);

//LIBFT
long int	ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_digit(char c);

#endif
