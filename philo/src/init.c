/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:49:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/01 18:15:36 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_letter(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_arguments(int argc, char **argv)
{
	int	i;

	if (argc > 6 || argc < 5)
		return (1);
	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	if (ft_check_letter(argc, argv))
		return (1);
	return (0);
}

void	ft_create_mutex_forks(t_data *data, int num)
{
	int	i;

	data->mutex_forks = malloc(num * sizeof(pthread_mutex_t));
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&data->mutex_forks[i], 0);
		i++;
	}
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	if (ft_check_arguments(argc, argv))
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->quantity = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->optional_arg = ft_atoi(argv[5]);
	else
		data->optional_arg = 0;
	pthread_mutex_init(&(data->mutex_stdout), 0);
	ft_create_mutex_forks(data, data->quantity);
	data->start_time = ft_get_time();
	data->flag_die = 0;
	data->finished_philo = 0;
	return (0);
}

void	ft_init_philo(t_philo	*philos, t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i].num = i;
		philos[i].data = data;
		philos[i].finished_eating = 0;
		philos[i].last_meal = ft_current_time(data->start_time);
		i++;
	}
}
