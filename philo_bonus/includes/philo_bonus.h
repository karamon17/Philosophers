/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:27:18 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/04 18:53:49 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
	long long			start_time;
	int					optional_arg;
	pid_t				*pid;
	int					flag_die;
	sem_t				**sem_forks;
}					t_data;

// typedef struct s_philo
// {
// 	struct s_data	*data;
// 	int				num;
// 	pthread_t		threads;
// 	long long		last_meal;
// 	int				is_dead;
// 	int				finished_eating;
// 	int				flag_finished;
// 	pthread_mutex_t	mutex_last_meal;
// 	pthread_mutex_t	mutex_eating;
// }					t_philo;

int			ft_atoi(const char *str);
int			ft_init_data(t_data *data, int argc, char **argv);
void		ft_usleep(int ms);
long long	ft_get_time(void);
long long	ft_current_time(long long start_time);
void 		ft_print(t_data *data, int i, char *str);

#endif