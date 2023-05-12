/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/12 12:01:25 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_infos	*ft_init(int ac, char **av)
{
	t_infos	*infos;

	if (ac != 5 && ac != 6)
		ft_exit(NULL, ERR_ARG);
	infos = malloc(sizeof(*infos));
	if (!infos)
		ft_exit(NULL, ERR_ARG);
	memset(infos, 0, sizeof(*infos));
	pthread_mutex_init(&infos->write, NULL);
	get_infos(infos, ac, av);
	fork_set(infos);
	philo_set(infos);
	printf("nb_philo : %d, t_die : %d, t_eat : %d, t_sleep : %d, \
	nb_cycle : %d\n", infos->nb_philo, infos->t_die, \
	infos->t_eat, infos->t_sleep, infos->nb_cycle);
	return (infos);
}

void	get_infos(t_infos *infos, int ac, char **av)
{
	infos->nb_philo = ft_atoi(av[1]);
	infos->t_die = ft_atoi(av[2]);
	infos->t_eat = ft_atoi(av[3]);
	infos->t_sleep = ft_atoi(av[4]);
	infos->ac = ac;
	if (infos->nb_philo < 1 || infos->t_die < 0 || \
	infos->t_eat < 0 || infos->t_sleep < 0)
		ft_exit(infos, ERR_ARG);
	if (ac == 6)
	{
		infos->nb_cycle = ft_atoi(av[5]);
		if (infos->nb_cycle < 0)
			ft_exit(infos, ERR_ARG);
	}
	else
		infos->nb_cycle = 1;
}

void	fork_set(t_infos *infos)
{
	int	i;

	infos->tab_fork = malloc(sizeof(pthread_mutex_t) * infos->nb_philo);
	if (!infos->tab_fork)
		ft_exit(infos, ERR_MAL);
	i = -1;
	while (++i < infos->nb_philo)
		pthread_mutex_init(&infos->tab_fork[i], NULL);
}

void	philo_set(t_infos *infos)
{
	int	i;

	infos->tab_philo = malloc(sizeof(t_philo) * infos->nb_philo);
	if (!infos->tab_philo)
		ft_exit(infos, ERR_MAL);
	memset(infos->tab_philo, 0, sizeof(t_philo) * infos->nb_philo);
	i = -1;
	while (++i < infos->nb_philo)
	{
		infos->tab_philo[i].id = i + 1;
		infos->tab_philo[i].infos = infos;
	}
}
