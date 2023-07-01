/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:51:25 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/01 19:45:00 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_is_die(void	*philo)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *) philo;
	while (1)
	{
		i = 0;
		while (i < philos->data->quantity)
		{
			if (philos[i].data->time_to_die < (ft_current_time(philos->data->start_time) - philos[i].last_meal))
			{
				pthread_mutex_lock(&philos->data->mutex_stdout);
				printf("%lld Philo %d died\n", ft_current_time(philos->data->start_time), i + 1);
				pthread_mutex_unlock(&philos->data->mutex_stdout);
				philos->data->flag_die = 1;
				return (NULL);
			}
			// if (philos[i].finished_eating == philos->data->optional_arg)
			// {
			// 	philos->data->finished_philo++;
			// 	if (philos->data->finished_philo == philos->data->quantity)
			// 		return (NULL);
			// }
			i++;
		}
	}
	return (NULL);
}

