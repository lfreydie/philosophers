/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/09 12:33:44 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_init(int ac, char **av)
{
	t_data	*gen;

	if (ac != 5 && ac != 6)
		ft_exit(NULL, ARGN_ERR);
	gen = malloc(sizeof(*gen));
	if (!gen)
		ft_exit(NULL, MALLOC_ERR);
	memset(gen, 0, sizeof(*gen));
	pthread_mutex_init(&gen->lock_write, NULL);
	pthread_mutex_init(&gen->lock_dead, NULL);
	set_data(gen, ac, av);
	fork_set(gen);
	philo_set(gen);
	return (gen);
}

void	set_data(t_data *gen, int ac, char **av)
{
	gen->nb_philo = ft_atoi(av[1]);
	gen->time.die = ft_atoi(av[2]);
	gen->time.eat = ft_atoi(av[3]);
	gen->time.sleep = ft_atoi(av[4]);
	if (gen->nb_philo < 0 || gen->time.die < 0 || \
	gen->time.eat < 0 || gen->time.sleep < 0)
		ft_exit(gen, ARG_ERR);
	if (ac == 6)
	{
		gen->cycle = true;
		gen->nb_cycle = ft_atoi(av[5]);
		if (gen->nb_cycle < 0)
			ft_exit(gen, ARG_ERR);
	}
}

void	fork_set(t_data *gen)
{
	int	i;

	gen->fork = malloc(sizeof(pthread_mutex_t) * (gen->nb_philo));
	if (!gen->fork)
		ft_exit(gen, MALLOC_ERR);
	i = -1;
	while (++i < gen->nb_philo)
		pthread_mutex_init(&gen->fork[i], NULL);
}

void	philo_set(t_data *gen)
{
	int	i;

	gen->tab_philo = malloc(sizeof(t_philo) * gen->nb_philo);
	if (!gen->tab_philo)
		ft_exit(gen, MALLOC_ERR);
	memset(gen->tab_philo, 0, sizeof(t_philo) * gen->nb_philo);
	i = -1;
	while (++i < gen->nb_philo)
	{
		pthread_mutex_init(&gen->tab_philo[i].lock_philo, NULL);
		gen->tab_philo[i].id = i + 1;
		gen->tab_philo[i].r_fork = i;
		if (i == 0)
			gen->tab_philo[i].l_fork = gen->nb_philo - 1;
		else
			gen->tab_philo[i].l_fork = i - 1;
		gen->tab_philo[i].gen = gen;
	}
}
