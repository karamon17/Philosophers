/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:29:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/30 17:38:14 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_init_data(&data, argc, argv))
		return (write(2, "Error in arguments\n", 6));
	ft_run(data, data->number_of_philosophers);
	//free(data->phylosophers);
	free(data);
	return (0);
}
