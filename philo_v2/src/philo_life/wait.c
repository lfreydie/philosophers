/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:59:48 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 16:55:10 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_wait(t_philo *philo, int time)
{
	int	t_start;

	t_start = get_time(philo->gen);
	while (get_time(philo->gen) - t_start < time)
	{
		if (check_stop(philo))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_think(t_philo *philo, int time)
{
	if (check_stop(philo))
		return (FAILURE);
	print_status(run_time(philo->gen), philo, LOG_THINK);
	if (ft_wait(philo, time))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_sleep(t_philo *philo, int time)
{
	if (check_stop(philo))
		return (FAILURE);
	print_status(run_time(philo->gen), philo, LOG_THINK);
	if (ft_wait(philo, time))
		return (FAILURE);
	return (SUCCESS);
}
