/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/24 15:56:12 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int ac, char **av)
{
	t_infos	*infos;
	int		status;
	int		i;

	infos = ft_init(ac, av);
	infos->t_start = get_time(infos);
	if (infos->nb_philo == 1)
		ft_one_philo(infos);
	else
		fork_process(infos);
	i = -1;
	while (++i < infos->nb_philo)
		waitpid(infos->tab_philo[i].pid, &status, 0);
	sem_end(infos);
	free_infos(infos);
	return (0);
}

void	fork_process(t_infos *infos)
{
	int		i;

	i = -1;
	while (++i < infos->nb_philo)
	{
		infos->tab_philo[i].pid = fork();
		if (infos->tab_philo[i].pid < 0)
			ft_exit(infos, ERR);
		else if (infos->tab_philo[i].pid == 0)
		{
			infos->tab_philo[i].last_meal = infos->t_start;
			ft_launch(&infos->tab_philo[i]);
			free_infos(infos);
			exit (0);
		}
	}

}

void	ft_launch(t_philo *perso)
{
	if (perso->id % 2 == 0)
		usleep(200);
	while (perso->nb_meal < perso->infos->nb_cycle)
	{
		if (!ft_eat(perso))
			break ;
		if (perso->infos->ac == 6)
			perso->nb_meal++;
		if (!ft_sleep(perso))
			break ;
		if (!ft_think(perso))
			break ;
	}
}

void	ft_one_philo(t_infos *infos)
{
	infos->tab_philo[0].last_meal = infos->t_start;
	sem_wait(infos->forks);
	write_msg(&infos->tab_philo[0], "%d %d has taken a fork\n");
	ft_waiting(&infos->tab_philo[0], infos->t_die);
	sem_post(infos->forks);
	free_infos(infos);
	sem_end(infos);
	exit (0);
}
