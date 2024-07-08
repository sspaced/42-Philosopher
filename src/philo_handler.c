/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:21:52 by root              #+#    #+#             */
/*   Updated: 2024/07/08 21:08:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int await_ready(t_philo *philo)
{
	pthread_mutex_lock(philo->ready_mutex);
	if (*(philo->ready) == 1)
		return (pthread_mutex_unlock(philo->ready_mutex), 1);
	return (pthread_mutex_unlock(philo->ready_mutex), 0);
}

int check_dead(t_philo *philo, time_t sleep)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	//printf("time between 2 meal : %ld\n", ((((tv.tv_sec*1000) + (tv.tv_usec / 1000) + sleep) - (philo->last_meal_time + philo->start_time))));
	if (((((tv.tv_sec*1000) + (tv.tv_usec / 1000) + sleep) - (philo->last_meal_time + philo->start_time))) > philo->params.ttd)
	{
		*(philo->dead) = 1;
		dying(philo);
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	}
	return (pthread_mutex_unlock(philo->dead_mutex), 0); 
}

void dying(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d died\n", (((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time), philo->philo_id);
}

int	thinking(t_philo *philo)
{
	struct timeval tv;
	
	if (check_dead(philo, 0))
		return (1);
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", (((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time), philo->philo_id);
}

int	forking(t_philo *philo)
{
	struct timeval tv;
	
	if (check_dead(philo, 0))
		return (1);
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", ((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time, philo->philo_id);
}

int eating(t_philo *philo)
{
	struct timeval tv;
	
	if (check_dead(philo, philo->params.tte))
		return (1);
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", ((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time, philo->philo_id);
	philo->last_meal_time = ((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time + philo->params.tte;
}

int sleeping(t_philo *philo)
{
	struct timeval tv;
	
	if (check_dead(philo, philo->params.tts))
		return (1);
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", ((tv.tv_sec*1000) + (tv.tv_usec / 1000)) - philo->start_time, philo->philo_id);
}

void	*routine_function(void *arg)
{
	t_philo *philo;
	struct timeval tv;

	philo = (t_philo *)arg;
	
	while (1)
		if (await_ready(philo))
			break;
	gettimeofday(&tv, NULL);
	philo->start_time = ((tv.tv_sec*1000) + (tv.tv_usec / 1000));
	while (1)
	{
		if (thinking(philo))
			break;
		pthread_mutex_lock(philo->rigth_fork_mutex);
		if(forking(philo))
			break;
		pthread_mutex_lock(philo->left_fork_mutex);
		if (forking(philo))
			break;
		if (eating(philo))
			break;
		usleep(philo->params.tte);
		pthread_mutex_unlock(philo->rigth_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		if (sleeping(philo))
			break;
		usleep(philo->params.tts);
	}
	pthread_mutex_unlock(philo->rigth_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}

void	start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	int *ready;
	t_philo		*philos_tab;
	
	//create philos_nb + 1 thread to monitor death
	philos_tab = init_philos_tab(nb_philo, ttd, tte, tts, philo_eat_list);
	init_philos_fork(philos_tab, nb_philo);
	index = 0;
	ready = philos_tab[0].ready;
	while (index < nb_philo)
	{
		pthread_create(&(philos_tab[index].thread), NULL, &routine_function, &(philos_tab[index]));
		index++;
	}
	pthread_mutex_lock(philos_tab[0].ready_mutex);
	*ready = 1;
	pthread_mutex_unlock(philos_tab[0].ready_mutex);
	index = 0;
	while(index < nb_philo)
	{
		pthread_join(philos_tab[index].thread, NULL);
		index++;
	}
}

void display(int philo_id, int status)
{
	//lock
	//printf("Philo ... , status ...");
	//unlock
}
