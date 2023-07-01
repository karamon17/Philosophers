/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:27:18 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/01 11:17:50 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data
{
	int					quantity;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					optional_arg;
	pthread_mutex_t		mutex_stdout;
	struct s_philo		*philo_array;
	pthread_mutex_t		*mutex_forks;
}					t_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				num;
	pthread_t		threads;
	int				left_fork;
	int				right_fork;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_meal;
	int				is_dead;
	int				finished_eating;
}					t_philo;

int		ft_atoi(const char *str);
void	ft_init_forks(t_data *data);
int		ft_init_data(t_data **data, int argc, char **argv);
void	ft_run(t_data *data, int num);
void	ft_init_philo(t_philo	*philos, t_data *data, int num);
void	ft_usleep(int ms);

#endif