/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:35:11 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 13:54:08 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av, char **environ)
{
	t_infos	*gen;
	int		i;

	if (!*environ)
		ft_exit(NULL, ENV_ERR);
	if (ac == 2 && !ft_memcmp(av[1], HELP, 6))
		return (print_helper(), FAILURE);
	gen = ft_init(ac, av);
	i = -1;
	gen->time.start = get_time() + 2000;
	if (gen->nb_philo == 1)
		one_philo(gen);
	else
	{
		while (++i < gen->nb_philo)
		{
			gen->tab_philo[i].last_meal = gen->time.start;
			if (pthread_create(&gen->tab_philo[i].th_philo, NULL, \
			philo_life, &gen->tab_philo[i]))
				ft_exit(gen, THREAD_ERR);
		}
	}
	free_data(gen);
}
