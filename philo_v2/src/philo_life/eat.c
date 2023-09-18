/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:59:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 17:35:16 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo, int time)
{
	if (take_forks(philo))
		return (FAILURE);
	if (check_stop)
		return (drop_forks(philo), FAILURE);
	print_status(run_time(philo->gen), philo, LOG_EAT);
	if (ft_wait(philo, time))
		return (drop_forks(philo), FAILURE);
	return (drop_forks(philo), SUCCESS);
}


int	take_forks(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(&philo->gen->fork[philo->l_fork]);
		if (check_stop(philo))
			return \
			(pthread_mutex_unlock(&philo->gen->fork[philo->l_fork]), FAILURE);
		print_status(run_time(philo->gen), philo, LOG_FORK);
		pthread_mutex_lock(&philo->gen->fork[philo->r_fork]);
		if (check_stop(philo))
			return (drop_forks(philo), FAILURE);
		print_status(run_time(philo->gen), philo, LOG_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->gen->fork[philo->r_fork]);
		if (check_stop(philo))
			return \
			(pthread_mutex_unlock(&philo->gen->fork[philo->r_fork]), FAILURE);
		print_status(run_time(philo->gen), philo, LOG_FORK);
		pthread_mutex_lock(&philo->gen->fork[philo->l_fork]);
		if (check_stop(philo))
			return (drop_forks(philo), FAILURE);
		print_status(run_time(philo->gen), philo, LOG_FORK);
	}
	return (SUCCESS);
}

void	drop_forks(t_philo *philo)
	{
	if (!philo->id % 2)
	{
		pthread_mutex_unlock(&philo->gen->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->gen->fork[philo->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->gen->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->gen->fork[philo->r_fork]);
	}
}
