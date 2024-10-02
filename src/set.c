/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 13:11:25 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	set_fork_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork_state = state;
	pthread_mutex_unlock(&philo->fork_mutex);
}

void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meals_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->last_meals_mutex);
}

void	set_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_count += 1;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_mutex);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->dead_mutex);
}
