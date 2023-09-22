/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:09:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/22 17:24:01 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_process(t_infos *gen)
{
	int		i;

	i = -1;
	while (++i < gen->nb_philo)
	{
		gen->tab_philo[i].pid = fork();
		if (gen->tab_philo[i].pid < 0)
			ft_exit(gen, FAILED);
		else if (gen->tab_philo[i].pid == 0)
		{
			gen->tab_philo[i].last_meal = gen->time.start;
			ft_launch(&gen->tab_philo[i]);
			free_infos(gen);
			exit (0);
		}
	}
	sem_wait(gen->death);
}

void	ft_launch(t_philo *philo)
{
	while (get_time() < philo->gen->time.start)
		usleep(200);
	if (pthread_create(&philo->th_philo, NULL, check_all, philo))
		return ;
	if (pthread_create(&philo->th_all, NULL, meal_check, philo))
		return (pthread_join(philo->th_philo, NULL), ft_sem_close(philo->gen));
	if (!(philo->id % 2))
	{
		print_status(philo, LOG_THINK);
		ft_wait(philo->gen->time.eat);
	}
	while (!death_check(philo->gen))
	{
		ft_eat(philo);
		if (check_ate_full(philo))
			break ;
		print_status(philo, LOG_SLEEP);
		ft_wait(philo->gen->time.sleep);
		print_status(philo, LOG_THINK);
		ft_wait(philo->gen->time.think);
	}
	pthread_join(philo->th_philo, NULL);
	pthread_join(philo->th_all, NULL);
	ft_sem_close(philo->gen);
}

void	one_philo(t_infos *gen)
{
	while (get_time() < gen->time.start)
		usleep(200);
	printf("%d 1 %s", run_time(gen), LOG_FORK);
	usleep(gen->time.die * 1000);
	printf("%d 1 %s", run_time(gen), LOG_DEAD);
	ft_sem_close(gen);
}
