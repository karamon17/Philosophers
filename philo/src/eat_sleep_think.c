/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:18:16 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/01 14:55:27 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *phil)
{
	if (phil->num == 0)
		pthread_mutex_lock(&phil->data->mutex_forks[phil->data->quantity]);
	else
		pthread_mutex_lock(&phil->data->mutex_forks[phil->num - 1]);
	pthread_mutex_lock(&phil->data->mutex_stdout);
	if (phil->data->flag_die)
	{
		if (phil->num == 1)
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->data->quantity]);
		else
			pthread_mutex_unlock(&phil->data->mutex_forks[phil->num - 1]);
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		return ;
	}
	printf("%lld Philo %d take left fork\n", ft_current_time(phil->data->start_time), phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	pthread_mutex_lock(&phil->data->mutex_forks[phil->num]);
	pthread_mutex_lock(&phil->data->mutex_stdout);
	if (phil->data->flag_die)
	{
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->num + 1]);
		return ;
	}
	printf("%lld Philo %d take right fork\n", ft_current_time(phil->data->start_time), phil->num + 1);
	phil->last_meal = ft_current_time(phil->data->start_time); //пока без мьютикса
	printf("%lld Philo %d eating\n", ft_current_time(phil->data->start_time), phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	ft_usleep(phil->data->time_to_eat);
	pthread_mutex_unlock(&phil->data->mutex_forks[phil->num]);
	if (phil->num == 0)
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->data->quantity]);
	else
		pthread_mutex_unlock(&phil->data->mutex_forks[phil->num - 1]);
	phil->finished_eating++; //пока без мьютикса
}

void	ft_sleep(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->mutex_stdout);
	printf("%lld Philo %d sleeping\n", ft_current_time(phil->data->start_time), phil->num + 1);
	pthread_mutex_unlock(&phil->data->mutex_stdout);
	ft_usleep(phil->data->time_to_sleep);
}
