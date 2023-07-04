/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:26:21 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 18:56:36 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_open_sem(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->quantity)
	{
		data->sem_forks[i] = sem_open("forks", O_CREAT, 0644, 1);
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
	data->start_time = ft_get_time();
	data->flag_die = 0;
	data->pid = malloc(sizeof(pid_t) * data->quantity);
	data->sem_forks = malloc(sizeof(sem_t *) * data->quantity);
	ft_open_sem(data);
	return (0);
}
