/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:59:33 by lfreydie          #+#    #+#             */
/*   Updated: 2023/07/06 15:18:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*gen;

	if (ac == 2 && !ft_memcmp(av[2], HELP, 6))
		return (print_helper, FAILURE);
	gen = ft_init(ac, av);
	return (SUCCESS);
}
