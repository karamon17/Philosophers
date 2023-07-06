/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:34:12 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/06 10:08:34 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_data *data, int i)
{
	sem_wait(data->sem_forks);
	ft_print(data, i, "has taken a fork");
	if (data->quantity == 1)
	{
		ft_usleep(data->time_to_die + 10);
		sem_post(data->sem_forks);
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
	while (1)
	{
		sem_wait(data->sem_count_eating);
		if (data->optional_arg && data->philo[i].finished_eating
			>= data->optional_arg)
			break ;
		sem_post(data->sem_count_eating);
		ft_eat(data, i);
		sem_wait(data->sem_count_eating);
		if (data->optional_arg && data->philo[i].finished_eating
			>= data->optional_arg)
			break ;
		sem_post(data->sem_count_eating);
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
}

void	ft_kill(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->quantity)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = -1;
			while (++i < data->quantity)
				kill(data->philo[i].pid, SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_close(data->sem_last_meal);
	sem_close(data->sem_count_eating);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("count_eating");
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
		{
			pthread_create(&data->philo[i].is_dead, NULL, ft_is_dead,
				data->philo + i);
			if (data->philo[i].num % 2 == 0)
				usleep(1000);
			ft_philo(data, i);
			pthread_join(data->philo[i].is_dead, NULL);
			exit(0);
		}
		i++;
	}
	ft_kill(data);
}
