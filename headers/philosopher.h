#ifndef PHILOSOPHER_H
# define philosopher_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	pthread_t	thread;
	t_params	params;
	int			philo_id;
	int			eat_nb;
	int			last_meal_time;
	int			dead;
}				t_philo;
//[FOLDER] src
//[FILE] philo_handler.c
void		start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);

//[FILE] philo_init.c
t_philo		*init_philos_tab(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);
t_params	init_params(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list);

#endif