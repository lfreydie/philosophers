/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/22 16:16:54 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_exit(t_infos *gen, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (gen)
		free_data(gen);
	exit (1);
}

void	free_data(t_infos *gen)
{
	int	i;

	if (gen)
	{
		if (gen->tab_philo && gen->nb_philo > 1)
		{
			i = -1;
			while (++i < gen->nb_philo)
				pthread_join(gen->tab_philo[i].th_philo, NULL);
			free(gen->tab_philo);
		}
		else if (gen->tab_philo)
			free(gen->tab_philo);
		pthread_mutex_destroy(&gen->lock_write);
		if (gen->fork)
		{
			i = -1;
			while (++i < gen->nb_philo)
				pthread_mutex_destroy(&gen->fork[i]);
			free(gen->fork);
		}
		free(gen);
	}
}
