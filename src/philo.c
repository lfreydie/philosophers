/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/17 15:34:32 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_infos	*infos;
	int		i;

	infos = ft_init(ac, av);
	i = -1;
	infos->t_start = get_time(infos);
	while (++i < infos->nb_philo)
	{
		infos->tab_philo[i].last_meal = infos->t_start;
		if (pthread_create(&infos->tab_philo[i].thread, NULL, \
		ft_launch, &infos->tab_philo[i]))
			ft_exit(infos, "error");
	}
	free_infos(infos);
}

void	*ft_launch(void *data)
{
	t_philo	*perso;

	perso = (t_philo *)data;
	if (perso->infos->nb_philo == 1)
		return (ft_one_philo(perso), NULL);
	if (perso->id % 2 == 0)
		usleep(200);
	while (perso->nb_meal < perso->infos->nb_cycle)
	{
		if (ft_eat(perso) == 1)
			break ;
		if (perso->infos->ac == 6)
			perso->nb_meal++;
		if (ft_sleep(perso) == 1)
			break ;
		if (ft_think(perso) == 1)
			break ;
	}
	return (NULL);
}

void	ft_one_philo(t_philo *perso)
{
	pthread_mutex_lock(&perso->infos->tab_fork[perso->r_fork]);
	if (write_lock(perso))
	{
		printf("%d %d has taken a fork\n", \
		running_time(perso->infos), perso->id);
		pthread_mutex_unlock(&perso->infos->write);
	}
	else
		pthread_mutex_unlock(&perso->infos->tab_fork[perso->r_fork]);
	ft_waiting(perso, perso->infos->t_die);
}
