/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:21:52 by root              #+#    #+#             */
/*   Updated: 2024/07/12 16:50:17 by root             ###   ########.fr       */
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

time_t elapsed_meal_time(t_philo *philo, time_t sleep)
{
	time_t time;

	time = current_time_ms();
	return (time + sleep - philo->last_meal_time - philo->start_time);
	
}
int check_dead(t_philo *philo, time_t sleep)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	if (elapsed_meal_time(philo, sleep) > philo->params.ttd)
	{
		*(philo->dead) = 1;
		dying(philo);
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	}
	return (pthread_mutex_unlock(philo->dead_mutex), 0); 
}

int display_info(t_philo *philo, char *info, int eat, int sleep)
{
	time_t	current_time;
	time_t	elapsed_time;

	current_time = current_time_ms();
	elapsed_time = current_time - philo->start_time;
	if (check_dead(philo, sleep))
		return (1);
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) != 1)
		printf("%ld %d %s\n", elapsed_time, philo->philo_id, info);
	pthread_mutex_unlock(philo->dead_mutex);
	if (eat == 1)
		philo->last_meal_time = current_time;
	return (0);
}

void dying(t_philo *philo)
{
	time_t	current_time;
	time_t	elapsed_time;
	
	current_time = current_time_ms();
	elapsed_time = current_time - philo->start_time;
	printf("%ld %d died\n", elapsed_time, philo->philo_id);
}

time_t	current_time_ms()
{
	struct timeval tv;
	time_t	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
void custom_usleep(int time_sleep)
{
    time_t start = current_time_ms();

    while (current_time_ms() - start < time_sleep / 1000)
    {
        usleep(1);
    } 
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
		if (display_info(philo, "is thinking", 0, 0))
			break;
		pthread_mutex_lock(philo->rigth_fork_mutex);
		if(display_info(philo, "has taken a fork", 0, 0))
			break;
		pthread_mutex_lock(philo->left_fork_mutex);
		if (display_info(philo, "has taken a fork", 0, 0))
			break;
		if (display_info(philo, "is eating", 1, philo->params.tte))
			break;
		custom_usleep(philo->params.tte);
		pthread_mutex_unlock(philo->rigth_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		if (display_info(philo, "is sleeping", 0, philo->params.tts))
			break;
		custom_usleep(philo->params.tts);
	}
}

void	start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	int *ready;
	t_philo		*philos_tab;
	
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
