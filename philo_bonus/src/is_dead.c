/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:03:23 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 18:08:36 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_is_dead(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->quantity)
		{
			sem_wait(data->sem_last_meal);
			if (ft_current_time(data->start_time) - data->philo[i].last_meal
				> data->time_to_die)
			{
				sem_wait(data->sem_print);
				printf("%lld %d died\n", ft_current_time(data->start_time),
					i + 1);
				sem_post(data->sem_print);
				sem_post(data->sem_last_meal);
				exit(1);
			}
			sem_post(data->sem_last_meal);
			sem_wait(data->sem_count_eating);
			if (data->optional_arg && data->philo[i].finished_eating
				>= data->optional_arg)
			{
				sem_post(data->sem_count_eating);
				return (NULL);
			}
			sem_post(data->sem_count_eating);
			i++;
		}
	}
	return (NULL);
}
