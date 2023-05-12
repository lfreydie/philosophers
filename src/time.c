/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:39:14 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/12 13:50:01 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	get_time(t_infos *infos)
{
	struct timeval	time;
	int				ms;

	if (gettimeofday(&time, NULL) < 0)
		ft_exit(infos, "didn't get time");
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	running_time(t_infos *infos)
{
	return ((get_time(infos) - infos->t_start));
}

int	ft_waiting(t_philo *perso, int time)
{
	while ((get_time(perso->infos) - perso->last_meal) < time)
	{
		usleep(1000);
		if (check_dead(*perso) == 1)
			return (1);
	}
	return (0);
}
