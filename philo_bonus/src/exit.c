/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/20 18:36:24 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_exit(t_infos *gen, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (gen)
		free_infos(gen);
	exit (FAILURE);
}

void	free_infos(t_infos *gen)
{
	if (gen)
	{
		if (gen->tab_philo)
			free(gen->tab_philo);
		free(gen);
	}
}

void	sem_end(t_infos *gen)
{
	if (gen->forks)
	{
		sem_close(gen->forks);
		sem_unlink("/forks");
	}
	if (gen->lock_write)
	{
		sem_close(gen->lock_write);
		sem_unlink("/lock_write");
	}
	if (gen->death)
	{
		sem_close(gen->death);
		sem_unlink("/death");
	}
	if (gen->check)
	{
		sem_close(gen->check);
		sem_unlink("/check");
	}
	if (gen->meal)
	{
		sem_close(gen->meal);
		sem_unlink("/meal");
	}
}

void	ft_sem_close(t_infos *gen)
{
	if (gen->forks)
		sem_close(gen->forks);
	if (gen->lock_write)
		sem_close(gen->lock_write);
	if (gen->death)
		sem_close(gen->death);
	if (gen->check)
		sem_close(gen->check);
	if (gen->meal)
		sem_close(gen->meal);
}
