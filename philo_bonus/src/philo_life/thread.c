/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:41:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/20 19:09:55 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*check_all(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// printf("1.1 id = %d\n", philo->id);
	sem_wait(philo->gen->death);
	sem_wait(philo->gen->check);
	philo->gen->is_dead = true;
	sem_post(philo->gen->check);
	sem_post(philo->gen->death);
	return (NULL);
}

void	*meal_check(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		// printf("2.0 id = %d\n", philo->id);
		if (death_check(philo->gen))
		{
			// printf("2.1 id = %d\n", philo->id);
			break ;
			// printf("2.2 id = %d\n", philo->id);
		}
		// printf("2.3 id = %d\n", philo->id);
		sem_wait(philo->gen->meal);
		if (get_time() - philo->last_meal > philo->gen->time.die)
		{
			sem_post(philo->gen->meal);
			philo_death(philo);
			break ;
		}
		if (philo->nb_meal >= philo->gen->nb_cycle && philo->gen->cycle)
		{
			usleep(philo->gen->time.die);
			sem_post(philo->gen->meal);
			sem_post(philo->gen->check);
			break ;
		}
		sem_post(philo->gen->meal);
		usleep(1000);
	}
	return (NULL);
}
