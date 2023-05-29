/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:13:56 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/24 17:33:04 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * res);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	check_dead(t_philo *perso)
{
	pthread_mutex_lock(&perso->infos->write);
	pthread_mutex_lock(&perso->infos->check_dead);
	if (perso->infos->dead == 1)
	{
		pthread_mutex_unlock(&perso->infos->check_dead);
		pthread_mutex_unlock(&perso->infos->write);
		return (ERR);
	}
	else if ((get_time(perso->infos) - perso->last_meal) >= perso->infos->t_die)
	{
		perso->infos->dead = 1;
		perso->last_meal = running_time(perso->infos);
		printf("%d %d died\n", running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->check_dead);
		pthread_mutex_unlock(&perso->infos->write);
		return (ERR);
	}
	pthread_mutex_unlock(&perso->infos->check_dead);
	pthread_mutex_unlock(&perso->infos->write);
	return (SUCCESS);
}

int	write_msg(t_philo *perso, char *msg)
{
	int	time;

	pthread_mutex_lock(&perso->infos->write);
	pthread_mutex_lock(&perso->infos->check_dead);
	if (perso->infos->dead == 1)
	{
		pthread_mutex_unlock(&perso->infos->check_dead);
		pthread_mutex_unlock(&perso->infos->write);
		return (ERR);
	}
	else if ((get_time(perso->infos) - perso->last_meal) >= perso->infos->t_die)
	{
		perso->infos->dead = 1;
		perso->last_meal = running_time(perso->infos);
		printf("%d %d died\n", running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->check_dead);
		pthread_mutex_unlock(&perso->infos->write);
		return (ERR);
	}
	pthread_mutex_unlock(&perso->infos->check_dead);
	time = get_time(perso->infos);
	printf(msg, time - perso->infos->t_start, perso->id);
	pthread_mutex_unlock(&perso->infos->write);
	return (time);
}
