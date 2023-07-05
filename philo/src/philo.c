/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/31 15:16:35 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_infos	*infos;
	int		i;

	infos = ft_init(ac, av);
	i = -1;
	infos->t_start = get_time(infos) + 2000;
	if (infos->nb_philo == 1)
	{
		infos->tab_philo[0].last_meal = infos->t_start;
		if (pthread_create(&infos->tab_philo[0].thread, NULL, \
		ft_one_philo, &infos->tab_philo[0]))
			ft_exit(infos, "error");
	}
	else
	{
		while (++i < infos->nb_philo)
		{
			infos->tab_philo[i].last_meal = infos->t_start;
			if (pthread_create(&infos->tab_philo[i].thread, NULL, \
			ft_launch, &infos->tab_philo[i]))
				ft_exit(infos, "error");
		}
	}
	free_infos(infos);
}

void	*ft_launch(void *data)
{
	t_philo	*perso;

	perso = (t_philo *)data;
	while (get_time(perso->infos) < perso->infos->t_start)
		usleep(200);
	if (!(perso->id % 2))
	{
		if (!ft_pre_think(perso))
			return (NULL);
	}
	while (perso->nb_meal < perso->infos->nb_cycle)
	{
		if (!ft_eat(perso))
			break ;
		if (perso->infos->ac == 6)
			perso->nb_meal++;
		if (!ft_sleep(perso))
			break ;
		if (perso->nb_meal >= perso->infos->nb_cycle)
			break ;
		if (!ft_think(perso))
			break ;
	}
	return (NULL);
}

void	*ft_one_philo(void *data)
{
	t_philo	*perso;

	perso = (t_philo *)data;
	pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
	if (!write_msg(perso, "%d %d has taken a fork\n"))
		return \
		(pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]), NULL);
	ft_waiting(perso, perso->infos->t_die);
	pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	return (NULL);
}
