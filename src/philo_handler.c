/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:21:52 by root              #+#    #+#             */
/*   Updated: 2024/07/12 19:11:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	check_dead(t_philo *philo, time_t sleep)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	if (elapsed_meal_time(philo, sleep) > philo->params.ttd)
	{
		*(philo->dead) = 1;
		display_died(philo);
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	}
	return (pthread_mutex_unlock(philo->dead_mutex), 0);
}

int		routine_helper(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	
	first_fork = malloc(sizeof(pthread_mutex_t));
	second_fork = malloc(sizeof(pthread_mutex_t));
	if (philo->rigth_fork_mutex < philo->left_fork_mutex)
	{
		first_fork = philo->rigth_fork_mutex;
		second_fork = philo->left_fork_mutex;
	}
	else 
	{
		first_fork = philo->left_fork_mutex;
		second_fork = philo->rigth_fork_mutex;
	}
	if (display_info(philo, "is thinking", 0, 0))
		return (0);
	pthread_mutex_lock(first_fork);
	if (display_info(philo, "has taken a fork", 0, 0))
		return (0);
	pthread_mutex_lock(second_fork);
	if (display_info(philo, "has taken a fork", 0, 0))
		return (0);
	if (display_info(philo, "is eating", 1, philo->params.tte))
		return (0);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	if (display_info(philo, "is sleeping", 2, philo->params.tts))
		return (0);
	return (1);
}

void	*thread_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
		if (await_ready(philo))
			break ;
	while (1)
	{
		if (!routine_helper(philo))
			break ;
		// if (display_info(philo, "is thinking", 0, 0))
		// 	break ;
		// pthread_mutex_lock(philo->rigth_fork_mutex);
		// if (display_info(philo, "has taken a fork", 0, 0))
		// 	break ;
		// pthread_mutex_lock(philo->left_fork_mutex);
		// if (display_info(philo, "has taken a fork", 0, 0))
		// 	break ;
		// if (display_info(philo, "is eating", 1, philo->params.tte))
		// 	break ;
		// pthread_mutex_unlock(philo->rigth_fork_mutex);
		// pthread_mutex_unlock(philo->left_fork_mutex);
		// if (display_info(philo, "is sleeping", 2, philo->params.tts))
		// 	break ;
	}
	return (NULL);
}

void	start_philosopher(int nb_philo, t_params params)
{
	int			index;
	int			*ready;
	t_philo		*philos_tab;

	philos_tab = init_philos_tab(nb_philo, params);
	init_philos_fork(philos_tab, nb_philo);
	index = 0;
	ready = philos_tab[0].ready;
	while (index < nb_philo)
	{
		pthread_create(&(philos_tab[index].thread), NULL,
			&thread_routine, &(philos_tab[index]));
		index++;
	}
	pthread_mutex_lock(philos_tab[0].ready_mutex);
	*ready = 1;
	pthread_mutex_unlock(philos_tab[0].ready_mutex);
	index = 0;
	while (index < nb_philo)
	{
		pthread_join(philos_tab[index].thread, NULL);
		index++;
	}
}
