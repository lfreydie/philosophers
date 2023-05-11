/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/11 15:11:35 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_take_fork(pthread_mutex_t fork, t_philo *perso)
{
	pthread_mutex_lock(&fork);
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d has taken a fork", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
}

void	ft_eat(t_philo *perso)
{
	ft_take_fork(perso->infos->tab_fork[perso->r_fork], perso);
	ft_take_fork(perso->infos->tab_fork[perso->l_fork], perso);
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d is eating", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	ft_waiting(perso, perso->infos->t_eat);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->l_fork]);
}

void	ft_think(t_philo *perso)
{
	int	t_think;
}

void	ft_sleep(t_philo *perso)
{
	pthread_mutex_lock(&perso->infos->write);
	printf("%d %d is sleeping", running_time(perso->infos), perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	ft_waiting(perso, perso->infos->t_sleep);
}
