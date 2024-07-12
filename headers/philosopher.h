#ifndef PHILOSOPHER_H
# define philosopher_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

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
	pthread_mutex_t *left_fork_mutex;
	pthread_mutex_t *ready_mutex;
	pthread_mutex_t *dead_mutex;
}				t_philo;
//[FOLDER] src
//[FILE] philo_handler.c
void		start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);

//[FILE] philo_init.c
t_philo		*init_philos_tab(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);
t_params	init_params(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);
void		init_philos_fork(t_philo *philos_tab, int nb_philo);
void		init_philos_status_mutex(t_philo *philos_tab, int nb_philo);
void		init_philos_status(t_philo *philos_tab, int nb_philo);
int			thinking(t_philo *philo);
int			forking(t_philo *philo);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
void		dying(t_philo *philo);
int			check_dead(t_philo *philo, time_t sleep);
int			display_info(t_philo *philo, char *info, int eat, int sleep);
time_t		current_time_ms();

#endif