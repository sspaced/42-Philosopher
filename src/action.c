/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 15:21:32 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	lock_forks(t_philo *philo, int fork_aquire)
{
	while (fork_aquire < 2)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->fork_state == 0)
		{
			fork_aquire += 1;
			philo->fork_state = 1;
			if (!display_info(philo, "has taken a fork"))
				return (pthread_mutex_unlock(&philo->fork_mutex), 0);
		}
		pthread_mutex_unlock(&philo->fork_mutex);
		if (philo->table->params.nb_philo == 1)
			return (pthread_mutex_unlock(&philo->fork_mutex), 0);
		pthread_mutex_lock(&philo->next->fork_mutex);
		if (philo->next->fork_state == 0)
		{
			fork_aquire += 1;
			philo->next->fork_state = 1;
			if (!display_info(philo, "has taken a fork"))
				return (pthread_mutex_unlock(&philo->next->fork_mutex), 0);
		}
		pthread_mutex_unlock(&philo->next->fork_mutex);
		usleep(1);
	}
	return (1);
}

int	philo_eat(t_philo *philo)
{
	int	fork_aquire;

	fork_aquire = 0;
	if (!lock_forks(philo, fork_aquire))
		return (0);
	if (!display_info(philo, "is eating"))
		return (0);
	custom_usleep(philo->table->params.tte, philo);
	set_meal(philo);
	set_last_meal_time(philo);
	set_fork_state(philo, 0);
	set_fork_state(philo->next, 0);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!display_info(philo, "is sleeping"))
		return (0);
	custom_usleep(philo->table->params.tts, philo);
	return (1);
}
