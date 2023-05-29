/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/29 19:01:42 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	take_forks(t_philo *perso)
{
	sem_wait(perso->infos->forks);
	if (!write_msg(perso, "%d %d has taken a fork\n"))
		return \
		(sem_post(perso->infos->forks), ERR);
	sem_wait(perso->infos->forks);
	if (!write_msg(perso, "%d %d has taken a fork\n"))
		return (sem_post(perso->infos->forks),
			sem_post(perso->infos->forks), ERR);
	return (SUCCESS);
}

int	ft_eat(t_philo *perso)
{
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
	sem_post(perso->infos->forks);
	return (SUCCESS);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	if (perso->infos->t_eat > perso->infos->t_sleep)
		t_think = (perso->infos->t_die - \
		(perso->infos->t_eat + perso->infos->t_sleep)) / 2;
	else
		t_think = 0;
	if (!write_msg(perso, "%d %d is thinking\n"))
		return (ERR);
	if (perso->infos->t_die >= 2 * perso->infos->t_eat)
		return (ft_waiting(perso, t_think));
	else
		return (ft_waiting(perso, perso->infos->t_die));
}

int	ft_pre_think(t_philo *perso)
{
	int	t_think;

	t_think = perso->infos->t_eat / 2;
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
