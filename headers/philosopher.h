/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:23:56 by root              #+#    #+#             */
/*   Updated: 2024/07/12 19:05:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params
{
	int			nb_philo;
	int			ttd;
	int			tte;
	int			tts;
	int			*philo_eat_list;
}				t_params;

typedef struct s_philo
{
	pthread_t		thread;
	t_params		params;
	int				philo_id;
	int				eat_nb;
	time_t			last_meal_time;
	time_t			start_time;
	int				*dead;
	int				*ready;
	pthread_mutex_t	*rigth_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*ready_mutex;
	pthread_mutex_t	*dead_mutex;
}				t_philo;
//[FOLDER] src
//[FILE] philo_handler.c
void		start_philosopher(int nb_philo, t_params params);
int			check_dead(t_philo *philo, time_t sleep);
void		*thread_routine(void *arg);

//[FILE] philo_init.c
t_philo		*init_philos_tab(int nb_philo, t_params	params);
t_params	init_params(int ttd, int tte, int tts, int *philo_eat_list);
void		init_philos_fork(t_philo *philos_tab, int nb_philo);
void		init_philos_status_mutex(t_philo *philos_tab, int nb_philo);
void		init_philos_status(t_philo *philos_tab, int nb_philo);

//[FILE] philo_utils.c
int			await_ready(t_philo *philo);
time_t		elapsed_meal_time(t_philo *philo, time_t sleep);
time_t		current_time_ms(void);
void		custom_usleep(int time_sleep);

//[FILE] philo_display.c
void		display_died(t_philo *philo);
int			display_info(t_philo *philo, char *info, int type, int sleep);
#endif