/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/15 11:51:31 by heda-sil         ###   ########.fr       */
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
# include <stdbool.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			nbr_meals;
	bool		full;
	long long	last_meal;
	t_dinner	*dinner;
	pthread_t	monitor;
}	t_philo;

typedef struct s_dinner
{
	int			nbr_philos;
	long long	time_die;
	long long	time_eat;
	long long	time_sleep;
	int			nbr_eats;
	int			philos_full;
	long long	start_time;
	int			nbr_forks;
	t_philo		*philo;
	sem_t		*sem_print;
	sem_t		*sem_forks;
	sem_t		*sem_end;
	sem_t		*sem_eat;
	sem_t		*sem_time;
}	t_dinner;

//VALIDATE
int			is_number(char *arg);
int			validate_args(char **args);
int			verify_args(int argc, char **argv);

//ROUTINE
void		philo_life(t_philo *philo);
void		print(t_philo *philo, char *str);

//UTILS
long long	get_times(void);
void		set_table(t_dinner *dinner);
void		create_philos(t_dinner *dinner, int ac, char **av);
void		kill_philos(t_dinner *dinner);

//LIBFT
long long	ft_atoll(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_digit(char c);

#endif
