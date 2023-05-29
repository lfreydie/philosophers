/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:04:27 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/29 19:05:35 by lfreydie         ###   ########.fr       */
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
