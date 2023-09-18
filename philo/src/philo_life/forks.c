/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:04:27 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/18 17:03:26 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->fork[philo->r_fork]);
	if (check_dead(philo))
		return \
		(pthread_mutex_unlock(&philo->gen->fork[philo->r_fork]), FAILURE);
	print_status(philo, LOG_FORK);
	pthread_mutex_lock(&philo->gen->fork[philo->l_fork]);
	if (check_dead(philo))
		return (FAILURE);
	print_status(philo, LOG_FORK);
	return (SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->gen->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->gen->fork[philo->r_fork]);
}
