/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:34:12 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 18:59:43 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_data *data, int i)
{
	sem_wait(data->sem_forks[i]);
	ft_print(data, i, "has taken a fork");
	ft_print(data, i, "has taken a fork");
	ft_print(data, i, "is eating");
	sem_post(data->sem_forks[i]);
	ft_usleep(data->time_to_eat);
}

void	ft_sleep(t_data *data, int i)
{
	sem_wait(data->sem_forks[i]);
	ft_print(data, i, "is sleeping");
	sem_post(data->sem_forks[i]);
	ft_usleep(data->time_to_sleep);
}

void	ft_think(t_data *data, int i)
{
	sem_wait(data->sem_forks[i]);
	ft_print(data, i, "is thinking");
	sem_post(data->sem_forks[i]);
}

void	ft_philo(t_data *data, int i)
{
	while (1)
	{
		sem_wait(data->sem_forks[i]);
		if (ft_current_time(data->start_time) > data->time_to_die)
		{
			sem_wait(data->sem_forks[i]);
			ft_print(data, i, "died");
			exit(0);
		}
		sem_post(data->sem_forks[i]);
		ft_eat(data, i);
		ft_sleep(data, i);
		ft_think(data, i);
	}
}

void	ft_run(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			ft_philo(data, i);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
