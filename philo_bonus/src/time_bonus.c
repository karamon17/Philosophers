/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:35:23 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 18:30:46 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_current_time(long long start_time)
{
	struct timeval	t1;
	long long		milliseconds;

	gettimeofday(&t1, NULL);
	milliseconds = (t1.tv_sec * 1000 + t1.tv_usec / 1000) - start_time;
	return (milliseconds);
}

long long	ft_get_time(void)
{
	struct timeval	t1;
	long long		milliseconds;

	gettimeofday(&t1, NULL);
	milliseconds = (t1.tv_sec * 1000 + t1.tv_usec / 1000);
	return (milliseconds);
}

void	ft_usleep(int ms)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < ms)
		usleep(ms / 10);
}
