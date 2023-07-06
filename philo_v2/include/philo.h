/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/07/06 15:19:14 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time
{
	int	start;
	int	die;
	int	eat;
	int	sleep;
	int	think;
}	t_time;

typedef struct s_philo
{
	pthread_t		th_philo;
	pthread_t		th_monitor;
	pthread_mutex_t	lock_philo;
	bool			stop;
	int				id;
	int				r_fork;
	int				l_fork;
	int				last_meal;
	int				nb_meal;
	t_data			*gen;
}	t_philo;

typedef struct s_data
{
	t_philo			*tab_philo;
	int				nb_philo;
	t_time			time;
	bool			cycle;
	int				nb_cycle;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_dead;
	bool			dead;
}	t_data;

# define SUCCESS	0
# define FAILURE	1
# define FAILED		"Failed"
# define HELP		"--help"
# define ARG_ERR	"Invalid argument"
# define ARGN_ERR	"Invalid number of arguments"
# define MALLOC_ERR	"Malloc failed"
# define THREAD_ERR	"pthread_create failed"

# define LOG_FORK	"has taken a fork\n"
# define LOG_EAT	"is eating\n"
# define LOG_SLEEP	"is sleeping\n"
# define LOG_THINK	"is thinking\n"
# define LOG_DEAD	"died\n"

//	MONITOR

//	PHILO_LIFE

//	PHILO_OUT

//	PRINT
//		PRINT_HELPER
void	print_helper(void);

//	UTILS
//		FT_MEMCMP
int		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
