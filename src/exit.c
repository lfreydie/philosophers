/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/11 15:18:46 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_exit(t_infos *infos, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (infos)
		free_infos(infos);
}

void	free_infos(t_infos *infos)
{
	int	i;

	if (infos)
	{
		pthread_mutex_destroy(&infos->write);
		if (infos->tab_fork)
		{
			i = -1;
			while (++i < infos->nb_philo)
				pthread_mutex_destroy(&infos->tab_fork[i]);
			free(infos->tab_fork);
		}
		if (infos->tab_philo)
		{
			i = -1;
			while (++i < infos->nb_philo)
				pthread_mutex_destroy(&infos->tab_philo[i]);
			free(infos->tab_philo);
		}
	}
}
