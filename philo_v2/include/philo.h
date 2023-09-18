/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/10 16:56:47 by lefreydier       ###   ########.fr       */
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
	struct s_data	*gen;
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

//	MAIN
void	philo_process(void *data);
void	ft_one_dude(t_data *gen);

//	PHILO_LIFE
//		DEAD
void	monitoring_process(void *data);
int		check_stop(t_philo *philo);
//		WAIT
int		ft_wait(t_philo *philo, int time);
int		ft_think(t_philo *philo, int time);
int		ft_sleep(t_philo *philo, int time);
//		AGENDA
void	philo_life(t_philo *philo);
//		EAT

//	EXIT
void	ft_exit(t_data *gen, char *msg);
void	free_data(t_data *gen);

//	INIT
t_data	*ft_init(int ac, char **av);
void	set_data(t_data *gen, int ac, char **av);
void	fork_set(t_data *gen);
void	philo_set(t_data *gen);

//	PRINT
//		PRINT_HELPER
void	print_helper(void);
//		PRINT_STATUS
void	print_status(int time, t_philo *philo, char *msg);

//	UTILS
//		FT_MEMCMP
int		ft_memcmp(const void *s1, const void *s2, size_t n);
//		FT_ATOI
int		ft_atoi(const char *nptr);
//		FT_STRLEN
int		ft_strlen(const char *s);
//		TIME
int		get_time(t_data *gen);
int		run_time(t_data *gen);

#endif
