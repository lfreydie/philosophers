/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:55:57 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 14:51:00 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *gen, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (gen)
		free_data(gen);
	exit(1);
}

void	free_data(t_data *gen)
{
	int	i;

	if (gen)
	{
		if (gen->tab_philo)
		{
			i = -1;
			while (++i < gen->nb_philo)
			{
				pthread_mutex_destroy(&gen->tab_philo[i].lock_philo);
				pthread_join(gen->tab_philo[i].th_monitor, NULL);
				pthread_join(gen->tab_philo[i].th_philo, NULL);
			}
			free(gen->tab_philo);
		}
		if (gen->fork)
		{
			i = -1;
			while (++i < gen->nb_philo)
				pthread_mutex_destroy(&gen->fork[i]);
			free(gen->fork);
		}
		pthread_mutex_destroy(&gen->lock_write);
		pthread_mutex_destroy(&gen->lock_dead);
		free(gen);
	}
}
