/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:16:30 by root              #+#    #+#             */
/*   Updated: 2024/07/12 18:48:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	display_info(t_philo *philo, char *info, int type, int sleep)
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
	if (type == 1)
	{
		philo->last_meal_time = current_time;
		custom_usleep(philo->params.tte);
	}
	else if (type == 2)
		custom_usleep(philo->params.tts);
	return (0);
}

void	display_died(t_philo *philo)
{
	time_t	current_time;
	time_t	elapsed_time;

	current_time = current_time_ms();
	elapsed_time = current_time - philo->start_time;
	printf("%ld %d died\n", elapsed_time, philo->philo_id);
}
