/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:13:56 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 14:25:11 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_death(t_philo *philo)
{
	sem_wait(philo->gen->lock_write);
	sem_wait(philo->gen->check);
	if (!philo->gen->is_dead)
		printf("%d %d %s", run_time(philo->gen), philo->id, LOG_DEAD);
	philo->gen->is_dead = true;
	sem_post(philo->gen->death);
	sem_post(philo->gen->check);
	usleep(10000);
	sem_post(philo->gen->lock_write);
}

int	check_ate_full(t_philo *philo)
{
	int	ate;

	sem_wait(philo->gen->meal);
	ate = philo->full;
	sem_post(philo->gen->meal);
	if (ate)
	{
		ft_wait(philo->gen->time.die);
		sem_post(philo->gen->death);
	}
	return (ate);
}

int	death_check(t_infos *gen)
{
	int	dead;

	sem_wait(gen->check);
	dead = gen->is_dead;
	return (sem_post(gen->check), dead);
}
