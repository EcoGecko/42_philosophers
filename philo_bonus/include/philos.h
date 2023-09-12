/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/12 16:37:24 by heda-sil         ###   ########.fr       */
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
# include <pthread.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			nbr_meals;
	long		last_meal;
	t_dinner	*dinner;
	pthread_t	monitor;
}	t_philo;

typedef struct s_dinner
{
	int		nbr_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nbr_eats;
	int		philos_full;
	long	start_time;
	int		nbr_forks;
	t_philo	*philo;
	sem_t	*print;
	sem_t	*forks;
	sem_t	*end;
	sem_t	*vars;
}	t_dinner;

extern int	philos_full;

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
