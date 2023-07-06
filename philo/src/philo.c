/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:54:09 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/06 09:39:22 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_flag_die(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->mutex_flag_die);
	if (phil->data->flag_die)
	{
		pthread_mutex_unlock(&phil->data->mutex_flag_die);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->mutex_flag_die);
	return (0);
}

int	ft_check_flag_die2(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->mutex_stdout);
	pthread_mutex_lock(&phil->data->mutex_flag_die);
	if (phil->data->flag_die)
	{
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		pthread_mutex_unlock(&phil->data->mutex_flag_die);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->mutex_flag_die);
	return (0);
}

void	*ft_philo(void *pointer)
{
	t_philo	*phil;

	phil = (t_philo *) pointer;
	if (phil->num % 2 != 0)
		usleep(2000);
	while (1)
	{
		if (ft_check_flag_die(phil))
			return (NULL);
		ft_eat(phil);
		if (ft_check_flag_die(phil))
			return (NULL);
		ft_sleep(phil);
		if (ft_check_flag_die(phil))
			return (NULL);
		if (ft_check_flag_die2(phil))
			return (NULL);
		printf("%lld %d is thinking\n", ft_current_time
			(phil->data->start_time), phil->num + 1);
		pthread_mutex_unlock(&phil->data->mutex_stdout);
		if (ft_check_flag_die(phil))
			return (NULL);
	}
	return (NULL);
}

void	ft_destroy_mutexes(t_data *data, int num)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_stdout);
	pthread_mutex_destroy(&data->mutex_flag_die);
	while (i < num)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		pthread_mutex_destroy(&data->philo_array[i].mutex_eating);
		pthread_mutex_destroy(&data->philo_array[i].mutex_last_meal);
		i++;
	}
}

void	ft_run(t_data *data, int num)
{
	t_philo		*philos;
	int			i;

	philos = malloc(num * sizeof(t_philo));
	ft_init_philo(philos, data, num);
	data->philo_array = philos;
	i = 0;
	while (i < data->quantity)
	{
		pthread_create(&philos[i].threads, 0, ft_philo, &data->philo_array[i]);
		i++;
	}
	ft_is_die(philos);
	i = 0;
	while (i < data->quantity)
	{
		pthread_join(philos[i].threads, 0);
		i++;
	}
	ft_destroy_mutexes(data, data->quantity);
}
