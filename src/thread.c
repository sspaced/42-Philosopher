/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 16:33:55 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	start_threads(t_table *table)
{
	int		i;
	t_philo	*philo_head;
	t_philo	*philo_next;

	i = 0;
	pthread_mutex_lock(&table->ready_mutex);
	philo_head = table->philo;
	while (i < table->params.nb_philo)
	{
		philo_next = table->philo->next;
		if (pthread_create(&table->philo->thread,
				NULL, &thread_routine, table->philo))
			return (pthread_mutex_unlock(&table->ready_mutex), 0);
		table->philo = philo_next;
		i++;
	}
	table->philo = philo_head;
	table->start_time = current_time_ms();
	pthread_mutex_unlock(&table->ready_mutex);
	end_monitor(table);
	return (1);
}

int	join_threads(t_table *table)
{
	int		i;
	t_philo	*philo_head;
	t_philo	*philo_next;

	i = 0;
	philo_head = table->philo;
	while (i < table->params.nb_philo)
	{
		philo_next = table->philo->next;
		pthread_join(table->philo->thread, NULL);
		table->philo = philo_next;
		i++;
	}
	table->philo = philo_head;
	return (1);
}
