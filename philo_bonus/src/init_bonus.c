/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:26:21 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 19:14:21 by gkhaishb         ###   ########.fr       */
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
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_meal");
	sem_unlink("count_eating");
	data->sem_forks = sem_open("forks", O_CREAT, 0666, data->quantity);
	data->sem_print = sem_open("print", O_CREAT, 0666, 1);
	data->sem_last_meal = sem_open("last_meal", O_CREAT, 0666, 1);
	data->sem_count_eating = sem_open("count_eating", O_CREAT, 0666, 1);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED
		|| data->sem_last_meal == SEM_FAILED
		|| data->sem_count_eating == SEM_FAILED)
	{
		write(2, "Error: sem_open\n", 16);
		exit(1);
	}
}

void	ft_init_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->quantity)
	{
		philo[i].num = i + 1;
		philo[i].finished_eating = 0;
		philo[i].data = philo->data;
		philo[i].last_meal = 0;
		philo[i].pid = 0;
		i++;
	}
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	t_philo	*philos;

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
	philos = malloc(sizeof(t_philo) * data->quantity);
	data->philo = philos;
	philos->data = data;
	ft_open_sem(data);
	ft_init_philo(philos);
	return (0);
}
