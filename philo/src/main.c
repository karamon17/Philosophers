/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:29:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/30 14:22:46 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arguments(int argc, char **argv)
{
	int	i;

	if (argc > 6)
		return (1);
	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	return (0);
}

int	ft_init_data(t_data **data, int argc, char **argv)
{
	if (ft_check_arguments(argc, argv))
		return (1);
	*data = malloc(sizeof(t_data));
	(*data)->number_of_philosophers = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->optional_arg = ft_atoi(argv[5]);
	else
		(*data)->optional_arg = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_init_data(&data, argc, argv))
		return (printf("Error in arguments"));
	free(data);
	return (0);
}
