/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:27:33 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/21 12:04:58 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->gen->lock_write);
	if (death_check(philo->gen))
	{
		sem_post(philo->gen->lock_write);
		return ;
	}
	printf("%d %d %s", run_time(philo->gen), philo->id, msg);
	sem_post(philo->gen->lock_write);
}
