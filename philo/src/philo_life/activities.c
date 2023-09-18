/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/18 15:10:19 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (FAILURE);
	philo->last_meal = get_time();
	if (philo->last_meal == -1)
		return (drop_forks(philo), FAILURE);
	print_status(philo, LOG_EAT);
	if (ft_wait(philo, philo->gen->time.eat))
		return (drop_forks(philo), FAILURE);
	return (drop_forks(philo), SUCCESS);
}

int	ft_think(t_philo *philo)
{
	if (check_dead(philo))
		return (FAILURE);
	print_status(philo, LOG_THINK);
	return (ft_wait(philo, philo->gen->time.think));
}

int	ft_time_lag(t_philo *philo)
{
	int	time;

	time = philo->gen->time.eat / 2;
	if (check_dead(philo))
		return (FAILURE);
	print_status(philo, LOG_THINK);
	return (ft_wait(philo, time));
}

int	ft_sleep(t_philo *philo)
{
	if (check_dead(philo))
		return (FAILURE);
	print_status(philo, LOG_SLEEP);
	return (ft_wait(philo, philo->gen->time.sleep));
}
