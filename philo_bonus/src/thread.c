/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:41:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/29 15:41:07 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*wait_to_die(void *data)
{
	t_philo	*perso;

	perso = data;
	sem_wait(perso->infos->check_dead);
	usleep(perso->infos->t_die * 1000);
	if (perso->infos->ac == 6)
	{
		pthread_create(&perso->end_thread, NULL, wait_to_end, perso);
		sem_wait(perso->infos->check_dead);
		perso->infos->dead = 1;
		sem_post(perso->infos->check_dead);
		pthread_join(perso->end_thread, NULL);
	}
	else
	{
		sem_wait(perso->infos->check_dead);
		perso->infos->dead = 1;
		sem_post(perso->infos->check_dead);
	}
	return (NULL);
}

void	*wait_to_end(void *data)
{
	t_philo	*perso;

	perso = data;
	while (1)
	{
		if (perso->infos->dead == 1)
			break ;
		if (perso->nb_meal >= perso->infos->nb_cycle)
		{
			usleep(perso->infos->t_eat * 3000);
			sem_post(perso->infos->check_dead);
			break ;
		}
	}
	return (NULL);
}
