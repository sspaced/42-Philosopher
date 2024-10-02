/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:23:56 by root              #+#    #+#             */
/*   Updated: 2024/10/02 16:38:27 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_params
{
	int			nb_philo;
	int			ttd;
	int			tte;
	int			tts;
	int			max_meals;
}				t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	time_t			last_meal_time;
	pthread_mutex_t	last_meals_mutex;
	int				meals_count;
	pthread_mutex_t	meals_mutex;
	int				fork_state;
	pthread_mutex_t	fork_mutex;
	struct s_philo	*next;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	t_params		params;
	struct s_philo	*philo;
	time_t			start_time;
	int				dead;
	int				ready;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	write_mutex;
}				t_table;

//[FOLDER] src
//[FILE] parsing.c
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			check_arg(int arg_nb, char **args);
int			check_if_digit(int arg_nb, char **args);

//[FILE] display.c
void		display_died(t_philo *philo);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
int			display_info(t_philo *philo, char *info);

//[FILE] init.c
int			init_table_philo(t_table *table);
int			init_table_mutexes(t_table *table);
t_params	init_params(int arg_nb, char **args);
int			init_table(t_table *table, int arg_nb, char **args);

//[FILE] philos_list.c
t_philo		*philo_last(t_philo *lst);
void		philo_circular(t_table *table);
t_philo		*philo_create_node(t_table *table, int id);
void		philo_add_back(t_philo **lst, t_philo *new);

//[FILE] time_utils.c
time_t		current_time_ms(void);
void		custom_usleep(time_t time_sleep, t_philo *philo);

//[FILE] free.c
void		free_philo(t_table	*table);
void		destroy_mutexes(t_table	*table);

//[FILE] thread.c
int			join_threads(t_table *table);
int			start_threads(t_table *table);

//[FILE] set.c
void		set_meal(t_philo *philo);
void		set_last_meal_time(t_philo *philo);
void		set_fork_state(t_philo *philo, int state);
void		set_dead(t_philo *philo);

//[FILE] get.c
int			get_dead(t_philo *philo);

//[FILE] await.c
void		await_ready(t_philo *philo);

//[FILE] monitor.c
int			check_end(t_philo *philo);
int			check_dead(t_philo *philo);
void		end_monitor(t_table *table);

//[FILE] routine.c
void		*thread_routine(void *arg);
int			philo_routine(t_philo *philo);

//[FILE] action.c
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			lock_forks(t_philo *philo, int fork_aquire);

#endif