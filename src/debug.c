/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 02:43:54 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	display_philo_info(t_table *table)
{
	int		i;
	t_philo	*philo_head;
	t_philo	*philo_next;

	i = 0;
	philo_head = table->philo;
	while (table->philo && i < table->params.nb_philo)
	{
		philo_next = table->philo->next;
		printf("philo_id = %d\n", table->philo->id);
		table->philo = philo_next;
		i++;
	}
	table->philo = philo_head;
}
