/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/23 14:21:14 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks(t_philo *perso)
{
	if (!(perso->id % 2))
	{
		pthread_mutex_lock(&perso->infos->tab_fork[perso->l_fork]);
		if (!write_msg(perso, "%d %d has taken a fork\n"))
			return \
			(pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]), ERR);
		pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
		if (!write_msg(perso, "%d %d has taken a fork\n"))
			return (drop_forks(perso), ERR);
	}
	else
	{
		pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
		if (!write_msg(perso, "%d %d has taken a fork\n"))
			return \
			(pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]), ERR);
		pthread_mutex_lock(&perso->infos->tab_fork[perso->l_fork]);
		if (!write_msg(perso, "%d %d has taken a fork\n"))
			return (drop_forks(perso), ERR);
	}
	return (SUCCESS);
}

void	drop_forks(t_philo *perso)
	{
	if (!perso->id % 2)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	}
}

int	ft_eat(t_philo *perso)
{
	// if (!check_dead(perso))
	// 	return (ERR);
	if (!take_forks(perso))
		return (ERR);
	perso->last_meal = write_msg(perso, "%d %d is eating\n");
	if (!perso->last_meal)
		return (drop_forks(perso), ERR);
	if (!ft_waiting(perso, perso->infos->t_eat))
		return (drop_forks(perso), ERR);
	drop_forks(perso);
	return (SUCCESS);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	t_think = (perso->infos->t_die - \
	(perso->infos->t_eat + perso->infos->t_sleep)) / 2;
	if (!write_msg(perso, "%d %d is thinking\n"))
		return (ERR);
	return (ft_waiting(perso, t_think));
}

int	ft_sleep(t_philo *perso)
{
	if (!write_msg(perso, "%d %d is sleeping\n"))
		return (ERR);
	return (ft_waiting(perso, perso->infos->t_sleep));
}
