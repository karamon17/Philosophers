/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:03:23 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 19:59:06 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_is_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sem_last_meal);
		if (ft_current_time(philo->data->start_time) - philo->last_meal
			> philo->data->time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%lld %d died\n", ft_current_time(philo->data->start_time),
				philo->num);
			sem_post(philo->data->sem_last_meal);
			exit(1);
		}
		sem_post(philo->data->sem_last_meal);
		sem_wait(philo->data->sem_count_eating);
		if (philo->data->optional_arg && philo->finished_eating
			>= philo->data->optional_arg)
		{
			sem_post(philo->data->sem_count_eating);
			return (NULL);
		}
		sem_post(philo->data->sem_count_eating);
	}
	return (NULL);
}
