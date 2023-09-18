/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:59:33 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/10 17:10:53 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*gen;
	int		i;

	if (ac == 2 && !ft_memcmp(av[1], HELP, 6))
		return (print_helper(), FAILURE);
	gen = ft_init(ac, av);
	i = -1;
	gen->time.start = get_time(gen);
	if (gen->nb_philo == 1)
		ft_one_dude(gen);
	else
	{
		while (++i < gen->nb_philo)
		{
			if (pthread_create(gen->tab_philo[i].th_philo, NULL, \
			philo_process, &gen->tab_philo[i]))
				ft_exit(gen, THREAD_ERR);
		}
	}
	return (free_data(gen), SUCCESS);
}

void	philo_process(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	if (pthread_create(philo->th_monitor, NULL, \
	monitoring_process, &philo))
		ft_exit(philo->gen, THREAD_ERR);
	philo_life(philo);
}

void	ft_one_dude(t_data *gen)
{
	printf("%d 1 has taken a fork\n", run_time(gen));
	usleep(gen->time.die * 1000);
	printf("%d 1 died\n", run_time(gen));
	ft_exit(gen, NULL);
}
