/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:54:09 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/30 19:12:49 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *pointer)
{
	t_philo	*phil;

	phil = (t_philo *) pointer;
	while (1)
	{
		//lock(left);
		pthread_mutex_lock(&phil->data->mutex_for_stdout);
		printf("Philo %d take left fork\n", phil->num);
		pthread_mutex_unlock(&phil->data->mutex_for_stdout);
		//lock(right);
		pthread_mutex_lock(&phil->data->mutex_for_stdout);
		printf("Philo %d take right fork\n", phil->num);
		printf("Philo %d eating\n", phil->num);
		pthread_mutex_unlock(&phil->data->mutex_for_stdout);
		ft_usleep(phil->data->time_to_eat);
		//unlock(right);
		//unlock(left);
		pthread_mutex_lock(&phil->data->mutex_for_stdout);
		printf("Philo %d sleeping\n", phil->num);
		pthread_mutex_unlock(&phil->data->mutex_for_stdout);
		ft_usleep(phil->data->time_to_sleep);
		pthread_mutex_lock(&phil->data->mutex_for_stdout);
		printf("Philo %d thinking\n", phil->num);
		pthread_mutex_unlock(&phil->data->mutex_for_stdout);
	}
	return (NULL);

}

void	ft_run(t_data *data, int num)
{
	t_philo	*philos;
	int		i;

	philos = malloc(num * sizeof(t_philo));
	ft_init_philo(philos, data, num);
	data->philo_array = philos;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&philos[i].threads, 0, ft_philo, &data->philo_array[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philos[i].threads, 0);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_for_stdout);
}
