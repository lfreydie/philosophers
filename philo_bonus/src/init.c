/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 18:14:39 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_infos	*ft_init(int ac, char **av)
{
	t_infos	*gen;

	sem_unlink_all();
	if (ac != 5 && ac != 6)
		ft_exit(NULL, ARG_ERR);
	gen = malloc(sizeof(*gen));
	if (!gen)
		ft_exit(NULL, ARG_ERR);
	memset(gen, 0, sizeof(*gen));
	get_infos(gen, ac, av);
	gen->lock_write = ft_sem_open("/lock_write", 1);
	gen->death = ft_sem_open("/death", 1);
	gen->check = ft_sem_open("/check", 1);
	gen->meal = ft_sem_open("/meal", 1);
	gen->forks = ft_sem_open("/forks", gen->nb_philo);
	if (!gen->lock_write || !gen->death || !gen->forks \
		|| !gen->check || !gen->meal)
	{
		sem_end(gen);
		ft_exit(gen, ERR_SEM);
	}
	philo_set(gen);
	return (gen);
}

sem_t	*ft_sem_open(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		sem_unlink(name);
		sem = sem_open(name, O_CREAT, 0644, value);
	}
	return (sem);
}

void	get_infos(t_infos *gen, int ac, char **av)
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
		if (gen->nb_cycle <= 0)
			ft_exit(gen, ARG_ERR);
	}
	else
		gen->nb_cycle = 1;
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
		gen->tab_philo[i].gen = gen;
	}
}
