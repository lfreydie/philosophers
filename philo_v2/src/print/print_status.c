/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:27:33 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/10 13:32:33 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int time, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->gen->lock_write);
	printf("%d %d %s", time, philo->id, msg);
	pthread_mutex_unlock(&philo->gen->lock_write);
}
