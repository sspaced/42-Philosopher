/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 16:23:51 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	await_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->ready_mutex);
	pthread_mutex_unlock(&philo->table->ready_mutex);
	pthread_mutex_lock(&philo->last_meals_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->last_meals_mutex);
}
