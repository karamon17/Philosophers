/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:49:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/30 19:06:18 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arguments(int argc, char **argv)
{
	int	i;

	if (argc > 6)
		return (1);
	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	return (0);
}

// void	ft_init_forks(t_data *data)
// {
// 	int	i;

// 	data->phylosophers = malloc(data->number_of_philosophers * sizeof(int));
// 	i = 1;
// 	while (i <= data->number_of_philosophers)
// 	{
// 		data->phylosophers[i] = i;
// 		i++;
// 	}
// }

int	ft_init_data(t_data **data, int argc, char **argv)
{
	if (ft_check_arguments(argc, argv))
		return (1);
	*data = malloc(sizeof(t_data));
	(*data)->number_of_philosophers = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]) * 1000;
	(*data)->time_to_eat = ft_atoi(argv[3]) * 1000;
	(*data)->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		(*data)->optional_arg = ft_atoi(argv[5]);
	else
		(*data)->optional_arg = 0;
	pthread_mutex_init(&((*data)->mutex_for_stdout), 0);
	//ft_init_forks(*data);
	return (0);
}

void	ft_init_philo(t_philo	*philos, t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (i == 0)
			philos[i].left_fork = num;
		else
			philos[i].left_fork = i - 1;
		philos[i].right_fork = i + 1;
		philos[i].num = i;
		philos[i].data = data;
		i++;
	}
}
