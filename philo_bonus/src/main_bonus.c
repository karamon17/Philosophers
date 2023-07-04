/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:29:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 18:57:24 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_del_sem(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->quantity)
	{
		sem_close(data->sem_forks[i]);
		sem_unlink("forks");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_init_data(&data, argc, argv))
		return (write(2, "Error in arguments\n", 19));
	ft_run(&data);
	ft_del_sem(&data);
	return (0);
}
