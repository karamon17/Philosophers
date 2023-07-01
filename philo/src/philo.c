/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:54:09 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/01 19:55:24 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *pointer)
{
	t_philo	*phil;

	phil = (t_philo *) pointer;
	if (phil->num % 2 != 0)
		usleep(2000);
	while (1)
	{
		// if (phil->data->finished_philo == phil->data->quantity)
		// 	return (NULL);
		if (phil->data->flag_die)
			return (NULL);
		ft_eat(phil);
		if (phil->data->flag_die)
			return (NULL);
		ft_sleep(phil);
		if (phil->data->flag_die)
			return (NULL);
		pthread_mutex_lock(&phil->data->mutex_stdout);
		if (phil->data->flag_die)
		{
			pthread_mutex_unlock(&phil->data->mutex_stdout);
			return (NULL);
		}
		printf("%lld Philo %d is thinking\n", ft_current_time(phil->data->start_time), phil->num + 1);
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		if (phil->data->flag_die)
			return (NULL);
	}
	return (NULL);
}

void	ft_destroy_mutexes(t_data *data, int num)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_stdout);
	while (i < num)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
}

void	ft_run(t_data *data, int num)
{
	t_philo		*philos;
	int			i;
	pthread_t	check_die;

	philos = malloc(num * sizeof(t_philo));
	ft_init_philo(philos, data, num);
	data->philo_array = philos;
	i = 0;
	while (i < data->quantity)
	{
		pthread_create(&philos[i].threads, 0, ft_philo, &data->philo_array[i]);
		i++;
	}
	pthread_create(&check_die, 0, ft_is_die, philos);
	i = 0;
	while (i < data->quantity)
	{
		pthread_join(philos[i].threads, 0);
		i++;
	}
	pthread_join(check_die, 0);
	ft_destroy_mutexes(data, data->quantity);
}
