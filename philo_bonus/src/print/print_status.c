/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:27:33 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/20 18:38:46 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->gen->lock_write);
	if (!death_check(philo->gen))
	{
		sem_post(philo->gen->lock_write);
		return ;
	}
	printf(msg, run_time(philo->gen), philo->id);
	sem_post(philo->gen->lock_write);
}
