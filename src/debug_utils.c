/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:16:30 by root              #+#    #+#             */
/*   Updated: 2024/09/26 17:15:02 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	display_fork_pointer(t_philo *philo_tab, int nb_philo)
{
	int	index;

	index = 0;
	while (index < nb_philo)
	{
		printf("[%d] rigth_fork : %p\n",  philo_tab[index].philo_id, philo_tab[index].right_fork);
		if (index + 1 != nb_philo)
			printf("[%d] left_fork :  %p\n",  philo_tab[index + 1].philo_id, philo_tab[index + 1].left_fork);
		if (index + 1 == nb_philo)
			printf("[%d] left_fork :  %p\n",  philo_tab[0].philo_id, philo_tab[0].left_fork);
		printf("#####################\n");
		printf("[%d] right_fork_mutex : %p\n",  philo_tab[index].philo_id, philo_tab[index].right_fork_mutex);
		if (index + 1 != nb_philo)
			printf("[%d] left_fork_mutex :  %p\n",  philo_tab[index + 1].philo_id, philo_tab[index + 1].left_fork_mutex);
		if (index + 1 == nb_philo)
			printf("[%d] left_fork_mutex :  %p\n",  philo_tab[0].philo_id, philo_tab[0].left_fork_mutex);
		printf("#####################\n");
		index++;
	}
}
