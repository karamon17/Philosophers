/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:50:26 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 18:23:38 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sem(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_close(data->sem_last_meal);
	sem_close(data->sem_count_eating);
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
		ft_close_sem(data);
	}
}
