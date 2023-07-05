/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:27:18 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/07/05 14:43:21 by gkhaishb         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int					quantity;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			start_time;
	int					optional_arg;
	sem_t				*sem_forks;
	sem_t				*sem_last_meal;
	sem_t				*sem_print;
	sem_t				*sem_count_eating;
	struct s_philo		*philo;
}					t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pid_t			pid;
	int				num;
	pthread_t		is_dead;
	long long		last_meal;
	int				finished_eating;
}					t_philo;

int			ft_atoi(const char *str);
int			ft_init_data(t_data *data, int argc, char **argv);
void		ft_usleep(int ms);
long long	ft_get_time(void);
long long	ft_current_time(long long start_time);
void		ft_print(t_data *data, int i, char *str);
void		ft_kill(t_data *data);
void		ft_run(t_data *data);
void		*ft_is_dead(void *arg);

#endif