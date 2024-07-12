/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:15:20 by root              #+#    #+#             */
/*   Updated: 2024/07/12 18:31:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	await_ready(t_philo *philo)
{
	pthread_mutex_lock(philo->ready_mutex);
	if (*(philo->ready) == 1)
		return (pthread_mutex_unlock(philo->ready_mutex), 1);
	return (pthread_mutex_unlock(philo->ready_mutex), 0);
}

time_t	elapsed_meal_time(t_philo *philo, time_t sleep)
{
	time_t	time;

	time = current_time_ms();
	return (time + sleep - philo->last_meal_time - philo->start_time);
}

time_t	current_time_ms(void)
{
	struct timeval	tv;
	time_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	custom_usleep(int time_sleep)
{
	time_t	start;

	start = current_time_ms();
	while (current_time_ms() - start < time_sleep / 1000)
		usleep(1);
}
