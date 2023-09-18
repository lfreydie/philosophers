/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:13:56 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/18 15:10:23 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->lock_dead);
	if (philo->gen->dead == 1)
	{
		pthread_mutex_unlock(&philo->gen->lock_dead);
		return (FAILURE);
	}
	else if ((get_time() - philo->last_meal) > philo->gen->time.die)
	{
		philo->gen->dead = 1;
		pthread_mutex_unlock(&philo->gen->lock_dead);
		print_status(philo, LOG_DEAD);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->gen->lock_dead);
	return (SUCCESS);
}

