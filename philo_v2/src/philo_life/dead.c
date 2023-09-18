/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:53:48 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 16:48:28 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	monitoring_process(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	while (1)
	{
		pthread_mutex_lock(&philo->lock_philo);
		pthread_mutex_lock(&philo->gen->lock_dead);
		if (philo->gen->dead == true)
			philo->stop = true;
		else if ((run_time(philo->gen) - philo->last_meal) >= philo->gen->time.die)
		{
			print_status(run_time(philo->gen), philo, LOG_DEAD);
			philo->gen->dead = true;
			philo->stop = true;
		}
		pthread_mutex_unlock(&philo->gen->lock_dead);
		if (philo->gen->cycle == true && philo->gen->nb_cycle == philo->nb_meal)
			philo->stop = true;
		pthread_mutex_unlock(&philo->lock_philo);
		if (philo->stop == true)
			break;
	}
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_philo);
	if (philo->stop == true)
		return (pthread_mutex_unlock(&philo->lock_philo), FAILURE);
	return (pthread_mutex_unlock(&philo->lock_philo), SUCCESS);
}
