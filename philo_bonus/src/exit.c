/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/06/13 13:04:55 by lfreydie         ###   ########.fr       */
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
	if (infos->forks)
	{
		sem_close(infos->forks);
		sem_unlink("/forks");
	}
	// if (infos->start)
	// {
	// 	sem_close(infos->start);
	// 	sem_unlink("/start");
	// }
	if (infos->write)
	{
		sem_close(infos->write);
		sem_unlink("/write");
	}
	if (infos->check_dead)
	{
		sem_close(infos->check_dead);
		sem_unlink("/check_dead");
	}
}

void	ft_sem_close(t_infos *infos)
{
	if (infos->forks)
		sem_close(infos->forks);
	// if (infos->start)
	// 	sem_close(infos->start);
	if (infos->write)
		sem_close(infos->write);
	if (infos->check_dead)
		sem_close(infos->check_dead);
}
