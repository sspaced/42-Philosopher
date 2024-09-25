/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:15:20 by root              #+#    #+#             */
/*   Updated: 2024/09/25 23:06:03 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	await_ready(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->ready_mutex);
	gettimeofday(&tv, NULL);
	if (*(philo->ready) == 1)
	{
		philo->start_time = current_time_ms();
		philo->last_meal_time = philo->start_time;
		return (pthread_mutex_unlock(philo->ready_mutex), 1);
	}
	return (pthread_mutex_unlock(philo->ready_mutex), 0);
}

time_t	elapsed_meal_time(t_philo *philo, time_t sleep)
{
	time_t	time;

	time = current_time_ms();
	printf("elapsed_meal_time  : %ld\n", (time - philo->last_meal_time) + sleep);
	return ((time - philo->last_meal_time) + sleep);
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
	while (current_time_ms() - start < time_sleep)
		usleep(10);
}
