/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/25 15:47:36 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_infos	*ft_init(int ac, char **av)
{
	t_infos	*infos;

	if (ac != 5 && ac != 6)
		ft_exit(NULL, ERR_ARG);
	infos = malloc(sizeof(*infos));
	if (!infos)
		ft_exit(NULL, ERR_ARG);
	memset(infos, 0, sizeof(*infos));
	infos->write = ft_sem_open("/write", 1);
	if (!infos->write)
		ft_exit (infos, "1");
	infos->check_dead = ft_sem_open("/check_dead", 4);
	if (!infos->check_dead)
		ft_exit (infos, "2");
	get_infos(infos, ac, av);
	infos->forks = ft_sem_open("/forks", infos->nb_philo);
	if (!infos->forks)
		ft_exit(infos, ERR_MAL);
	philo_set(infos);
	printf("dead=%d, ac=%d, nb philo=%d, t die=%d, t eat=%d, t sleep=%d, nb cycle=%d\n",
		infos->dead, infos->ac, infos->nb_philo, infos->t_die, infos->t_eat, infos->t_sleep, infos->nb_cycle);
	return (infos);
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
