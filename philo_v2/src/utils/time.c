/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:53:34 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/09 13:12:19 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_data	*gen)
{
	struct timeval	time;
	int				ms;

	if (gettimeofday(&time, NULL) == -1)
		ft_exit(gen, "didn't get time");
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	run_time(t_data *gen)
{
	return (get_time(gen) - gen->time.start);
}
