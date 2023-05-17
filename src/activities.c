/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/17 18:28:46 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_take_forks(t_philo *perso)
{
	pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
	if (write_lock(perso))
	{
		printf("%d %d has taken a fork\n", \
		running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		return \
		(pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]), 1);
	pthread_mutex_lock(&perso->infos->tab_fork[perso->l_fork]);
	if (write_lock(perso))
	{
		printf("%d %d has taken a fork\n", \
		running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		return \
		(pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]), \
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]), 1);
	return (0);
}

int	ft_eat(t_philo *perso)
{
	int	ret;

	ret = 0;
	if (ft_take_forks(perso) == 1)
		return (1);
	if (write_lock(perso))
	{
		perso->last_meal = get_time(perso->infos);
		printf("%d %d is eating\n", running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		ret = 1;
	if (ft_waiting(perso, perso->infos->t_eat))
		ret = 1;
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
	return (ret);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	t_think = (perso->infos->t_die - \
	(perso->infos->t_eat + perso->infos->t_sleep)) / 2;
	if (write_lock(perso))
	{
		printf("%d %d is thinking\n", running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		return (1);
	return (ft_waiting(perso, t_think));
}

int	ft_sleep(t_philo *perso)
{
	if (write_lock(perso))
	{
		printf("%d %d is sleeping\n", running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		return (1);
	return (ft_waiting(perso, perso->infos->t_sleep));
}
