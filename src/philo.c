/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/11 15:45:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_infos	*infos;
	int		i;

	infos = ft_init(ac, av);
	i = -1;
	pthread_create(&infos->super, NULL, ft_supervisor, &infos);
	infos->t_start = get_time(infos);
	while (++i < infos->nb_philo)
	{
		pthread_create(&infos->tab_philo[i].thread, NULL, \
		ft_launch, &infos->tab_philo[i]);
		// error ?
	}
}

void	ft_launch(void *data)
{
	t_philo	*perso;

	perso = (t_philo *)data;
	ft_eat(perso);
	ft_sleep(perso);
	ft_think(perso);
}

void	ft_supervisor(void *data)
{
	t_infos	*infos;

	infos = data;
}
