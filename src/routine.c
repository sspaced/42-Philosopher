/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 13:54:48 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	await_ready(philo);
	if (!display_info(philo, "is thinking"))
		return (NULL);
	if (philo->id % 2)
	{
		custom_usleep(philo->table->params.tte, philo);
	}
	while (!(get_dead(philo)))
	{
		if (!philo_routine(philo))
			break ;
		usleep(1);
	}
	return (NULL);
}

int	philo_routine(t_philo *philo)
{
	if (!philo_eat(philo))
		return (0);
	if (!philo_sleep(philo))
		return (0);
	if (!display_info(philo, "is thinking"))
		return (0);
	return (1);
}
