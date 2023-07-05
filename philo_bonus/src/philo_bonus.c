/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:34:12 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 18:33:10 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_data *data, int i)
{
	sem_wait(data->sem_forks);
	ft_print(data, i, "has taken a fork");
	if (data->quantity == 1)
	{
		ft_usleep(data->time_to_die);
		pthread_join(data->philo[i].is_dead, NULL);
		exit(1);
	}
	sem_wait(data->sem_forks);
	ft_print(data, i, "has taken a fork");
	ft_print(data, i, "is eating");
	sem_wait(data->sem_count_eating);
	data->philo[i].finished_eating ++;
	sem_post(data->sem_count_eating);
	sem_wait(data->sem_last_meal);
	data->philo[i].last_meal = ft_current_time(data->start_time);
	sem_post(data->sem_last_meal);
	ft_usleep(data->time_to_eat);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
}

void	ft_philo(t_data *data, int i)
{
	pthread_create(&data->philo[i].is_dead, NULL, ft_is_dead, data);
	if (data->philo[i].num % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(data, i);
		ft_print(data, i, "is sleeping");
		ft_usleep(data->time_to_sleep);
		ft_print(data, i, "is thinking");
		sem_wait(data->sem_count_eating);
		if (data->optional_arg && data->philo[i].finished_eating
			>= data->optional_arg)
			break ;
		sem_post(data->sem_count_eating);
	}
	sem_post(data->sem_count_eating);
	pthread_join(data->philo[i].is_dead, NULL);
	exit(0);
}

void	ft_run(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->quantity)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
		{
			write(2, "Error: fork\n", 12);
			exit(1);
		}
		if (data->philo[i].pid == 0)
			ft_philo(data, i);
		i++;
	}
	ft_kill(data);
}
