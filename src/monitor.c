/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 14:06:12 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meals_mutex);
	if ((current_time_ms() - philo->last_meal_time) > philo->table->params.ttd
		&& philo->philo_state != 1)
	{
		set_dead(philo);
		pthread_mutex_unlock(&philo->last_meals_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->last_meals_mutex);
	return (1);
}

int	check_meals(t_philo *philo, int nb_max_meal)
{
	pthread_mutex_lock(&philo->meals_mutex);
	if (philo->meals_count == philo->table->params.max_meals)
		nb_max_meal++;
	pthread_mutex_unlock(&philo->meals_mutex);
	return (nb_max_meal);
}

void	end_monitor(t_table *table)
{
	int		nb_max_meal;
	t_philo	*philo_head;
	t_philo	*philo_next;

	nb_max_meal = 0;
	philo_head = table->philo;
	while (table->philo)
	{
		philo_next = table->philo->next;
		if (!check_dead(table->philo))
		{
			if (nb_max_meal !=  table->params.nb_philo)
				display_died(table->philo);
			break ;
		}
		nb_max_meal = check_meals(table->philo, nb_max_meal);
		if (nb_max_meal ==  table->params.nb_philo)
		{
			set_dead(table->philo);
			break ;
		}
		table->philo = philo_next;
		usleep(1);
	}
	table->philo = philo_head;
}
