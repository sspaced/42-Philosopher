/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 01:53:57 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	free_philo(t_table	*table)
{
	int		i;
	t_philo	*philo_next;

	i = 0;
	while (i < table->params.nb_philo && table->philo)
	{
		philo_next = table->philo->next;
		free(table->philo);
		table->philo = philo_next;
		i++;
	}
}

void	destroy_mutexes(t_table	*table)
{
	int		i;
	t_philo	*philo_next;

	i = 0;
	while (i < table->params.nb_philo && table->philo)
	{
		philo_next = table->philo->next;
		pthread_mutex_destroy(&table->philo->fork_mutex);
		pthread_mutex_destroy(&table->philo->meals_mutex);
		table->philo = philo_next;
		i++;
	}
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->ready_mutex);
	pthread_mutex_destroy(&table->write_mutex);
}
