/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:13:56 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 12:01:11 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all(t_infos *gen)
{
	int	dead;

	pthread_mutex_lock(&gen->lock_dead);
	dead = gen->dead;
	return (pthread_mutex_unlock(&gen->lock_dead), dead);
}

int	check_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->lock_dead);
	if ((get_time() - philo->last_meal) > philo->gen->time.die)
		return (pthread_mutex_unlock(&philo->gen->lock_dead), FAILURE);
	return (pthread_mutex_unlock(&philo->gen->lock_dead), SUCCESS);
}

int	philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->lock_dead);
	if (philo->gen->dead == true)
		return (pthread_mutex_unlock(&philo->gen->lock_dead), FAILURE);
	philo->gen->dead = true;
	pthread_mutex_unlock(&philo->gen->lock_dead);
	pthread_mutex_lock(&philo->gen->lock_write);
	printf("%d %d %s", run_time(philo->gen), philo->id, LOG_DEAD);
	pthread_mutex_unlock(&philo->gen->lock_write);
	return (FAILURE);
}
