/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/20 11:44:31 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_infos	*ft_init(int ac, char **av)
{
	t_infos	*infos;

	if (ac != 5 && ac != 6)
		ft_exit(NULL, ARGN_ERR);
	infos = malloc(sizeof(*infos));
	if (!infos)
		ft_exit(NULL, MALLOC_ERR);
	memset(infos, 0, sizeof(*infos));
	pthread_mutex_init(&infos->lock_write, NULL);
	pthread_mutex_init(&infos->lock_dead, NULL);
	get_infos(infos, ac, av);
	fork_set(infos);
	philo_set(infos);
	return (infos);
}

void	get_infos(t_infos *gen, int ac, char **av)
{
	int	t_max;

	gen->nb_philo = ft_atoi(av[1]);
	gen->time.die = ft_atoi(av[2]);
	gen->time.eat = ft_atoi(av[3]);
	gen->time.sleep = ft_atoi(av[4]);
	if (gen->nb_philo < 0 || gen->time.die < 0 || \
	gen->time.eat < 0 || gen->time.sleep < 0)
		ft_exit(gen, ARG_ERR);
	t_max = gen->time.eat;
	if (gen->time.eat < gen->time.sleep)
		t_max = gen->time.sleep;
	if (!(gen->nb_philo % 2) || gen->time.die >= 3 * t_max)
		gen->time.think = gen->time.eat - gen->time.sleep + 3;
	else
		gen->time.think = gen->time.die;
	if (ac == 6)
	{
		gen->cycle = true;
		gen->nb_cycle = ft_atoi(av[5]);
		if (gen->nb_cycle < 0)
			ft_exit(gen, ARG_ERR);
	}
	else
		gen->nb_cycle = 1;
}

void	fork_set(t_infos *gen)
{
	int	i;

	gen->fork = malloc(sizeof(pthread_mutex_t) * (gen->nb_philo));
	if (!gen->fork)
		ft_exit(gen, MALLOC_ERR);
	i = -1;
	while (++i < gen->nb_philo)
		pthread_mutex_init(&gen->fork[i], NULL);
}

void	philo_set(t_infos *gen)
{
	int	i;

	gen->tab_philo = malloc(sizeof(t_philo) * gen->nb_philo);
	if (!gen->tab_philo)
		ft_exit(gen, MALLOC_ERR);
	memset(gen->tab_philo, 0, sizeof(t_philo) * gen->nb_philo);
	i = -1;
	while (++i < gen->nb_philo)
	{
		gen->tab_philo[i].id = i + 1;
		if (i == 0)
		{
			gen->tab_philo[i].l_fork = gen->nb_philo - 1;
			gen->tab_philo[i].r_fork = i;
		}
		else
		{
			gen->tab_philo[i].l_fork = i;
			gen->tab_philo[i].r_fork = i - 1;
		}
		gen->tab_philo[i].gen = gen;
	}
}
