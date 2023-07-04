/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:51:25 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 13:31:19 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_is_die(t_philo *philos)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < philos->data->quantity)
		{
			//pthread_mutex_lock(&philos->mutex_last_meal);
			if (philos[i].data->time_to_die < (ft_current_time
					(philos->data->start_time) - philos[i].last_meal))
			{
				pthread_mutex_lock(&philos->data->mutex_stdout);
				printf("%lld %d died\n", ft_current_time(
						philos->data->start_time), i + 1);
				pthread_mutex_unlock(&philos->data->mutex_stdout);
				philos->data->flag_die = 1;
				return ;
			}
			//pthread_mutex_unlock(&philos->mutex_last_meal);
			// pthread_mutex_lock(&philos->mutex_eating);
			// if (philos->data->optional_arg && philos[i].finished_eating == philos->data->optional_arg)
			// {
			// 	philos->data->finished_philo++;
			// 	if (philos->data->finished_philo == philos->data->quantity)
			// 	{
			// 		pthread_mutex_unlock(&philos->mutex_eating);
			// 		philos->data->flag_die = 1;
			// 		return ;
			// 	}	
			// }
			// pthread_mutex_unlock(&philos->mutex_eating);
			i++;
		}
	}
	return ;
}

