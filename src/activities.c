/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/12 15:03:52 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_take_forks(t_philo *perso)
{
	pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
	if (check_dead(*perso) == 1)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		return (1);
	}
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d has taken a fork\n", \
	running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	pthread_mutex_lock(&perso->infos->tab_fork[perso->l_fork]);
	if (check_dead(*perso) == 1)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
		return (1);
	}
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d has taken a fork\n", \
	running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	if (check_dead(*perso) == 1)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *perso)
{
	if (check_dead(*perso) == 1)
		return (1);
	if (ft_take_forks(perso) == 1)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
		return (1);
	}
	pthread_mutex_lock(&perso->infos->write);
	perso->last_meal = get_time(perso->infos);
	printf("%d %d is eating\n", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	if (ft_waiting(perso, perso->infos->t_eat) == 1)
	{
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
		return (1);
	}
	// pthread_mutex_lock(&perso->infos->write);
	// printf("%d %d has finished eat\n", running_time(perso->infos), perso->id);
	// pthread_mutex_unlock(&perso->infos->write);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
	return (0);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	if (check_dead(*perso) == 1)
		return (1);
	t_think = (perso->infos->t_die - \
	(perso->infos->t_eat + perso->infos->t_sleep)) / 2;
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d is thinking\n", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	if (ft_waiting(perso, t_think) == 1)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *perso)
{
	if (check_dead(*perso) == 1)
		return (1);
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d is sleeping\n", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	if (ft_waiting(perso, perso->infos->t_sleep) == 1)
		return (1);
	return (0);
}
