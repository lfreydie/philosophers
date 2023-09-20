/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:13:56 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/20 19:01:22 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_death(t_philo *philo)
{
	sem_wait(philo->gen->check);
	if (philo->gen->is_dead == true)
		sem_post(philo->gen->check);
	philo->gen->is_dead = true;
	sem_post(philo->gen->check);
	sem_wait(philo->gen->lock_write);
	printf("%d %d %s", run_time(philo->gen), philo->id, LOG_DEAD);
	usleep(2000);
	sem_post(philo->gen->lock_write);
}

int	death_check(t_infos *gen)
{
	int	dead;

	sem_wait(gen->check);
	dead = gen->is_dead;
	return (sem_post(gen->check), dead);
}
