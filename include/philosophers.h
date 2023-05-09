/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/09 15:54:32 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			r_fork;
	int			l_fork;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	key;
	int				id;
}	t_fork;

typedef struct s_infos
{
	t_philo	*tab_philo;
	t_fork	*tab_fork;
}	t_infos;

# define ERR_ARG "arguments invalid\n"

#endif
