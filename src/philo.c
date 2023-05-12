/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/12 13:52:03 by lfreydie         ###   ########.fr       */
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
	while (perso->nb_meal <= perso->infos->nb_cycle)
	{
		if (ft_eat(perso) == 1)
			break ;
		pthread_mutex_lock(&perso->infos->write);
		printf("id_philo : %d, n_meal : %d, last_meal : %d\n", \
		perso->id, perso->nb_meal, perso->last_meal);
		pthread_mutex_unlock(&perso->infos->write);
		if (perso->infos->ac == 6)
			perso->nb_meal++;
		if (ft_sleep(perso) == 1)
			break ;
		if (ft_think(perso) == 1)
			break ;
	}
	return (NULL);
}
