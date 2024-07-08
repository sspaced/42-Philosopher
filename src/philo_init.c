/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:21:42 by root              #+#    #+#             */
/*   Updated: 2024/07/08 20:34:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

t_params init_params(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	t_params params;

	params.nb_philo = nb_philo;
	params.philo_eat_list = philo_eat_list;
	params.ttd = ttd;
	params.tte = tte;
	params.tts = tts;
	return (params);
}

t_philo	*init_philos_tab(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	t_philo	*philos_tab;
	t_params params;

	index = 0;
	philos_tab = malloc(nb_philo * sizeof(t_philo));
	if (!philos_tab)
		return (NULL);
	params = init_params(nb_philo, ttd, tte, tts, philo_eat_list);
	while (index < nb_philo)
	{
		philos_tab[index].params = params;
		philos_tab[index].philo_id = index;
		philos_tab[index].eat_nb = 0;
		philos_tab[index].last_meal_time = 0;
		philos_tab[index].start_time = 0;
		index++;
	}
	init_philos_fork(philos_tab, nb_philo);
	init_philos_status_mutex(philos_tab, nb_philo);
	init_philos_status(philos_tab, nb_philo);
	return (philos_tab);
}

void	init_philos_fork(t_philo *philos_tab, int nb_philo)
{
	int index;
	pthread_mutex_t *right_fork;
	
	index = 0;
	while (index < nb_philo)
	{
		right_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(right_fork, NULL);
		philos_tab[index].rigth_fork_mutex = right_fork;
		if (index != 0)
			philos_tab[index].left_fork_mutex = philos_tab[index - 1].rigth_fork_mutex;
		if ((index + 1) == nb_philo)
			philos_tab[0].left_fork_mutex = philos_tab[index].rigth_fork_mutex;
		index++;
	}
}

void init_philos_status_mutex(t_philo *philos_tab, int nb_philo)
{
	int index;
	pthread_mutex_t *dead_mutex;
	pthread_mutex_t *ready_mutex;

	dead_mutex = malloc(sizeof(pthread_mutex_t));
	ready_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(dead_mutex, NULL);
	pthread_mutex_init(ready_mutex, NULL);
	index = 0;
	while (index < nb_philo)
	{
		philos_tab[index].dead_mutex = dead_mutex;
		philos_tab[index].ready_mutex = ready_mutex;
		index++;
	}
}

void init_philos_status(t_philo *philos_tab, int nb_philo)
{
	int index;
	int *dead;
	int *ready;

	dead = malloc(sizeof(int));
	ready = malloc(sizeof(int));
	
	*dead = 0;
	*ready = 0;
	index = 0;
	while (index < nb_philo)
	{
		philos_tab[index].dead = dead;
		philos_tab[index].ready = ready;
		index++;
	}	
}
