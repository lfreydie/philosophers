/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/26 13:44:37 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	take_forks(t_philo *perso)
{
	// int	semval;

	sem_wait(perso->infos->forks);
	// sem_getvalue(perso->infos->forks, &semval);
	// printf("%d by %d\n", semval, perso->id);
	if (!write_msg(perso, "%d %d has taken a fork\n"))
		return \
		(sem_post(perso->infos->forks), ERR);
	sem_wait(perso->infos->forks);
	// sem_getvalue(perso->infos->forks, &semval);
	// printf("%d by %d\n", semval, perso->id);
	if (!write_msg(perso, "%d %d has taken a fork\n"))
		return (sem_post(perso->infos->forks),
			sem_post(perso->infos->forks), ERR);
	return (SUCCESS);
}

int	ft_eat(t_philo *perso)
{
	// int	semval;

	if (!take_forks(perso))
		return (ERR);
	perso->last_meal = write_msg(perso, "%d %d is eating\n");
	if (!perso->last_meal)
		return (sem_post(perso->infos->forks),
			sem_post(perso->infos->forks), ERR);
	if (!ft_waiting(perso, perso->infos->t_eat))
		return (sem_post(perso->infos->forks),
			sem_post(perso->infos->forks), ERR);
	sem_post(perso->infos->forks);
	// sem_getvalue(perso->infos->forks, &semval);
	// printf("%d dropped %d\n", semval, perso->id);
	sem_post(perso->infos->forks);
	// sem_getvalue(perso->infos->forks, &semval);
	// printf("%d dropped %d\n", semval, perso->id);
	return (SUCCESS);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	t_think = (perso->infos->t_die - \
	(perso->infos->t_eat + perso->infos->t_sleep)) / 2;
	if (!write_msg(perso, "%d %d is thinking\n"))
		return (ERR);
	if (perso->infos->t_die >= 2 * perso->infos->t_eat)
		return (ft_waiting(perso, t_think));
	else
		return (ft_waiting(perso, perso->infos->t_die));
}

int	ft_sleep(t_philo *perso)
{
	if (!write_msg(perso, "%d %d is sleeping\n"))
		return (ERR);
	return (ft_waiting(perso, perso->infos->t_sleep));
}
