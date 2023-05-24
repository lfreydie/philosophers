/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/24 17:23:17 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_exit(t_infos *infos, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (infos)
		free_infos(infos);
	exit (1);
}

void	free_infos(t_infos *infos)
{
	if (infos)
	{
		if (infos->tab_philo)
			free(infos->tab_philo);
		free(infos);
	}
}

void	sem_end(t_infos *infos)
{
	sem_close(infos->forks);
	sem_unlink("/forks");
	sem_close(infos->write);
	sem_unlink("/write");
	sem_close(infos->check_dead);
	sem_unlink("/check_dead");
}
