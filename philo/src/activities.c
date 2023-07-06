/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:06:12 by lfreydie          #+#    #+#             */
/*   Updated: 2023/07/06 13:17:57 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_eat(t_philo *perso)
{
	if (!take_forks(perso))
		return (ERR);
	perso->last_meal = write_msg(perso, "%d %d is eating\n");
	if (!perso->last_meal)
		return (drop_forks(perso), ERR);
	if (!ft_waiting(perso, perso->infos->t_eat))
		return (drop_forks(perso), ERR);
	drop_forks(perso);
	return (SUCCESS);
}

int	ft_think(t_philo *perso)
{
	int	t_think;

	if (!(perso->infos->nb_philo % 2))
		t_think = 0;
	else
		t_think = perso->infos->t_eat - 5;
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
