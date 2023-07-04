/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:18:16 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 14:19:13 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_left_fork(t_philo *phil)
{
	if (phil->num == 0)
		pthread_mutex_lock(&phil->data->mutex_forks[phil->num]);
	else
		pthread_mutex_lock(&phil->data->mutex_forks[phil->num - 1]);
	pthread_mutex_lock(&phil->data->mutex_stdout);
	if (phil->data->flag_die)
	{
		if (phil->num == 0)
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
		else
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num - 1]);
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		return (1);
	}
	printf("%lld %d has taken a fork\n", ft_current_time(phil->data->start_time),
		phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	return (0);
}

int	ft_right_fork(t_philo *phil)
{
	if (phil->data->quantity != 1)
	{
		if (phil->num == 0)
			pthread_mutex_lock(&phil->data->mutex_forks
			[phil->data->quantity - 1]);
		else
			pthread_mutex_lock(&phil->data->mutex_forks[phil->num]);
		pthread_mutex_lock(&phil->data->mutex_stdout);
	}
	else
		usleep(phil->data->time_to_die * 1000);
	if (phil->data->flag_die)
	{
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		if (phil->num == 0)
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
		else
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num - 1]);
		if (phil->num == 0)
			pthread_mutex_unlock(&phil->data->mutex_forks
			[phil->data->quantity - 1]);
		else
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", ft_current_time(phil->data->start_time),
		phil->num + 1);
	return (0);
}


void	ft_eat(t_philo *phil)
{
	if (ft_left_fork(phil) || ft_right_fork(phil))
		return ;
	pthread_mutex_lock(&phil->mutex_last_meal); //
	phil->last_meal = ft_current_time(phil->data->start_time);
	pthread_mutex_unlock(&phil->mutex_last_meal); //
	printf("%lld %d is eating\n", ft_current_time(phil->data->start_time),
		phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	ft_usleep(phil->data->time_to_eat);
	if (phil->num == 0)
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
	else
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->num - 1]);
	if (phil->num == 0)
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->data->quantity - 1]); //
	else
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
	pthread_mutex_lock(&phil->mutex_eating); //
	phil->finished_eating++;
	pthread_mutex_unlock(&phil->mutex_eating); //
}

void	ft_sleep(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->mutex_stdout);
	printf("%lld %d is sleeping\n", ft_current_time(phil->data->start_time),
		phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	ft_usleep(phil->data->time_to_sleep);
}
