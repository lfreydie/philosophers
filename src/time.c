/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:39:14 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/11 15:14:49 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	get_time(t_infos *infos)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
		ft_exit(infos, "didn't get time");
	return (current_time.tv_usec);
}

int	running_time(t_infos *infos)
{
	return ((get_time(infos) - infos->t_start) * 1000);
}

void	ft_waiting(t_philo *perso, int time)
{
	int	start;

	start = get_time(perso->infos);
	while ((get_time(perso->infos) - start) < time)
	{
		usleep(1000);
		check_dead(perso);
	}
}
