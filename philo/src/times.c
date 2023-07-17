/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heda-sil <heda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:17:46 by heda-sil          #+#    #+#             */
/*   Updated: 2023/07/17 22:17:46 by heda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/* Get the time and converts it to milliseconds */
long	get_times(void)
{
	struct timeval	time;
	long			times;

	gettimeofday(&time, NULL);
	times = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (times);
}
