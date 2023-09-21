/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 11:44:33 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->gen->forks);
	print_status(philo, LOG_FORK);
	sem_wait(philo->gen->forks);
	print_status(philo, LOG_FORK);
}

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, LOG_EAT);
	sem_wait(philo->gen->meal);
	philo->last_meal = get_time();
	philo->nb_meal++;
	sem_post(philo->gen->meal);
	ft_wait(philo->gen->time.eat);
	sem_post(philo->gen->forks);
	sem_post(philo->gen->forks);
}
