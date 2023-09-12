/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:15 by heda-sil          #+#    #+#             */
/*   Updated: 2023/09/12 16:41:21 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

/* Each fork and its state */
typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	mutex_fork;

}	t_fork;

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
	long		last_meal;
	int			nbr_meals;
	bool		died;
	bool		full;
	pthread_t	philo;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_dinner	*dinner;
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
	int				philos_full;
	long			start_time;
	bool			end_dinner;
	bool			death;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_time;
}	t_dinner;

//UTILS
int			check_death(t_philo *philo);
void		set_odd_forks(t_dinner *dinner, int i);
void		set_even_forks(t_dinner *dinner, int i);
void		set_table(t_dinner *dinner);
void		print(t_philo *philo, char *str);

//TIMES
long		get_times(void);

//VALIDATE
int			is_number(char *arg);
int			validate_args(char **args);
int			verify_input(int argc, char **argv);

//ROUTINE
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		death(t_philo *philo);

//LIBFT
long int	ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_digit(char c);


void		end_dinner(t_philo *philo);
#endif
