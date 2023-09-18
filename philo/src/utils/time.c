/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:39:14 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/18 15:46:51 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	struct timeval	time;
	int				ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	run_time(t_infos *gen)
{
	int	time;

	time = get_time();
	if (time == -1)
		return (time);
	return ((time - gen->time.start));
}

int	ft_wait(t_philo *philo, int time)
{
	int	start;

	if (time == 0)
		return (SUCCESS);
	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(500);
		if (check_dead(philo))
			return (FAILURE);
	}
	return (SUCCESS);
}
