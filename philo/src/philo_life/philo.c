/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 12:01:26 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (get_time() < philo->gen->time.start)
		usleep(200);
	if (!(philo->id % 2) && (ft_time_lag(philo)))
		return (NULL);
	while (philo->nb_meal < philo->gen->nb_cycle)
	{
		if (ft_eat(philo))
			break ;
		if (philo->gen->cycle == true)
			philo->nb_meal++;
		if (philo->nb_meal == philo->gen->nb_cycle)
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_think(philo))
			break ;
	}
	return (NULL);
}

void	one_philo(t_infos *gen)
{
	while (get_time() < gen->time.start)
		usleep(200);
	printf("%d 1 %s", run_time(gen), LOG_FORK);
	usleep(gen->time.die * 1000);
	printf("%d 1 %s", run_time(gen), LOG_DEAD);
}
