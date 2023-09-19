/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:27:33 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/19 18:36:23 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->gen->lock_write);
	if (!check_all(philo->gen))
	{
		printf("%d %d %s", run_time(philo->gen), philo->id, msg);
		pthread_mutex_unlock(&philo->gen->lock_write);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&philo->gen->lock_write);
	return (FAILURE);
}
