/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:51:25 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 15:29:42 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_count_eat(t_philo *philos)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < philos->data->quantity)
	{
		if (philos[i].flag_finished)
			count++;
		i++;
	}
	return (count);
}

int	ft_all_eat(t_philo *philos, int i)
{
	pthread_mutex_unlock(&philos[i].mutex_last_meal);
	pthread_mutex_lock(&philos[i].mutex_eating);
	if (philos->data->optional_arg && philos[i].finished_eating
		== philos->data->optional_arg)
	{
		philos[i].flag_finished = 1;
		if (ft_count_eat(philos) == philos->data->quantity)
		{
			pthread_mutex_unlock(&philos[i].mutex_eating);
			philos->data->flag_die = 1;
			return (1);
		}	
	}
	pthread_mutex_unlock(&philos[i].mutex_eating);
	return (0);
}

void	ft_is_die(t_philo *philos)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < philos->data->quantity)
		{
			pthread_mutex_lock(&philos[i].mutex_last_meal);
			if (philos->data->time_to_die < (ft_current_time
					(philos->data->start_time) - philos[i].last_meal))
			{
				pthread_mutex_lock(&philos->data->mutex_stdout);
				printf("%lld %d died\n", ft_current_time(
						philos->data->start_time), i + 1);
				pthread_mutex_unlock(&philos->data->mutex_stdout);
				philos->data->flag_die = 1;
				pthread_mutex_unlock(&philos[i].mutex_last_meal);
				return ;
			}
			if (ft_all_eat(philos, i))
				return ;
			i++;
		}
	}
	return ;
}

