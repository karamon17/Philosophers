/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:29:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/06 09:40:06 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_init_data(&data, argc, argv))
		return (write(2, "Error in arguments\n", 19));
	if (!data.quantity)
		return (0);
	ft_run(&data, data.quantity);
	free(data.mutex_forks);
	free(data.philo_array);
	return (0);
}
