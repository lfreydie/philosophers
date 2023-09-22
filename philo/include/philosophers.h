/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/22 16:03:01 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

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
	int				id;
	int				r_fork;
	int				l_fork;
	int				last_meal;
	int				nb_meal;
	struct s_infos	*gen;
}	t_philo;

typedef struct s_infos
{
	t_philo			*tab_philo;
	int				nb_philo;
	bool			dead;
	t_time			time;
	bool			cycle;
	int				nb_cycle;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_dead;
}	t_infos;

# define SUCCESS	0
# define FAILURE	1
# define FAILED		"Failed\n"
# define HELP		"--help\n"
# define ARG_ERR	"Invalid argument\n"
# define ARGN_ERR	"Invalid number of arguments\n"
# define MALLOC_ERR	"Malloc failed\n"
# define THREAD_ERR	"pthread_create failed\n"
# define ENV_ERR	"environment failed\n"

# define LOG_FORK	"has taken a fork\n"
# define LOG_EAT	"is eating\n"
# define LOG_SLEEP	"is sleeping\n"
# define LOG_THINK	"is thinking\n"
# define LOG_DEAD	"died\n"

//	INIT
t_infos	*ft_init(int ac, char **av);
void	get_infos(t_infos *gen, int ac, char **av);
void	fork_set(t_infos *gen);
void	philo_set(t_infos *gen);

//	EXIT
void	ft_exit(t_infos *gen, char *msg);
void	free_data(t_infos *gen);

//	PHILO_LIFE
//		ACTIVITIES
int		ft_eat(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_time_lag(t_philo *philo);
int		ft_sleep(t_philo *philo);
//		DEAD
int		check_all(t_infos *gen);
int		check_philo(t_philo *philo);
int		philo_death(t_philo *philo);
//		FORKS
int		take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
//		PHILO
void	*philo_life(void *data);
void	one_philo(t_infos *gen);

//	PRINT
//		PRINT_HELPER
void	print_helper(void);
//		PRINT_STATUS
int		print_status(t_philo *philo, char *msg);

//	UTILS
//		FT_LIB
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
//	TIME
int		get_time(void);
int		run_time(t_infos *gen);
int		ft_wait(t_philo *philo, int time);

#endif
