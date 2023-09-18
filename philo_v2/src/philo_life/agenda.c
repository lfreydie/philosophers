/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agenda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:56:29 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 17:08:52 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_life(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		if (ft_think(philo, (philo->gen->time.eat / 2)))
			return ;
	}
	while (1)
	{
		if (ft_eat(philo, philo->gen->time.eat))
			break;
		else if (philo->gen->cycle == true)
		{
			pthread_mutex_lock(&philo->lock_philo);
			philo->nb_meal++;
			pthread_mutex_unlock(&philo->lock_philo);
		}
		if (ft_sleep(philo, philo->gen->time.sleep))
			break;
		if (ft_think(philo, philo->gen->time.think))
			break;
	}
}
