/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:34:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/09/21 13:53:38 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>

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
	int				id;
	pid_t			pid;
	pthread_t		th_all;
	pthread_t		th_philo;
	int				last_meal;
	int				nb_meal;
	bool			full;
	struct s_infos	*gen;
}	t_philo;

typedef struct s_infos
{
	t_philo			*tab_philo;
	int				nb_philo;
	int				nb_cycle;
	t_time			time;
	bool			is_dead;
	bool			cycle;
	sem_t			*forks;
	sem_t			*lock_write;
	sem_t			*meal;
	sem_t			*death;
	sem_t			*check;
}	t_infos;

# define SUCCESS	0
# define FAILURE	1
# define FAILED		"Failed"
# define HELP		"--help"
# define ARG_ERR	"Invalid argument"
# define ARGN_ERR	"Invalid number of arguments"
# define MALLOC_ERR	"Malloc failed"
# define ERR_SEM 	"error semaphore\n"
# define THREAD_ERR	"pthread_create failed"
# define ENV_ERR	"environment failed"

# define LOG_FORK	"has taken a fork\n"
# define LOG_EAT	"is eating\n"
# define LOG_SLEEP	"is sleeping\n"
# define LOG_THINK	"is thinking\n"
# define LOG_DEAD	"died\n"

//	INIT
t_infos	*ft_init(int ac, char **av);
sem_t	*ft_sem_open(const char *name, unsigned int value);
void	get_infos(t_infos *gen, int ac, char **av);
void	philo_set(t_infos *gen);



//	UTILS
//		FT_LIB
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
//		TIME
int		get_time(void);
int		run_time(t_infos *gen);
void	ft_wait(int time);

//	PRINT
//		PRINT_HELPER
void	print_helper(void);
//		PRINT_STATUS
void	print_status(t_philo *philo, char *msg);

//	PHILO_LIFE
//		PHILO
void	fork_process(t_infos *gen);
void	ft_launch(t_philo *philo);
void	one_philo(t_infos *gen);
//		EAT
void	take_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
//		DEAD
void	philo_death(t_philo *philo);
int		check_ate_full(t_philo *philo);
int		death_check(t_infos *gen);
//		THREAD
void	*check_all(void *data);
void	*meal_check(void *data);

//	EXIT
void	ft_exit(t_infos *gen, char *msg);
void	free_infos(t_infos *gen);
void	sem_end(t_infos *gen);
void	sem_unlink_all(void);
void	ft_sem_close(t_infos *gen);

#endif
