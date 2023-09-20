/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:33:49 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/20 18:40:07 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_infos	*gen;
	int		status;
	int		i;

	if (ac == 2 && !ft_memcmp(av[1], HELP, 6))
		return (print_helper(), SUCCESS);
	gen = ft_init(ac, av);
	gen->time.start = get_time() + 2000;
	i = -1;
	if (gen->nb_philo == 1)
		one_philo(gen);
	else
	{
		fork_process(gen);
		while (++i < gen->nb_philo)
			waitpid(gen->tab_philo[i].pid, &status, 0);
		sem_end(gen);
	}
	free_infos(gen);
	return (SUCCESS);
}
