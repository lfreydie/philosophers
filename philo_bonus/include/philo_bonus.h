/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:34:18 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/26 13:38:50 by lefreydier       ###   ########.fr       */
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
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	pthread_t		thread;
	pid_t			pid;
	int				id;
	int				last_meal;
	int				nb_meal;
	struct s_infos	*infos;
}	t_philo;

typedef struct s_infos
{
	t_philo			*tab_philo;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*check_dead;
	int				dead;
	int				ac;
	int				nb_philo;
	int				t_start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_cycle;
}	t_infos;

# define ERR_ARG "arguments invalid\n"
# define ERR_MAL "error malloc\n"
# define ERR_SEM "error semaphore\n"
# define ERR 0
# define SUCCESS 1

//	INIT
t_infos	*ft_init(int ac, char **av);
sem_t	*ft_sem_open(const char *name, unsigned int value);
void	get_infos(t_infos *infos, int ac, char **av);
void	philo_set(t_infos *infos);

//	PHILO
void	fork_process(t_infos *infos);
void	ft_launch(t_philo *perso);
void	ft_one_philo(t_infos *infos);
void	*wait_to_die(void *data);

//	ACTIVITIES
int		take_forks(t_philo *perso);
int		ft_eat(t_philo *perso);
int		ft_think(t_philo *perso);
int		ft_sleep(t_philo *perso);

//	TIME
int		get_time(t_infos *infos);
int		running_time(t_infos *infos);
int		ft_waiting(t_philo *perso, int time);

//	UTILS
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);
int		check_dead(t_philo *perso);
int		write_msg(t_philo *perso, char *msg);

//	EXIT
void	ft_exit(t_infos *infos, char *msg);
void	free_infos(t_infos *infos);
void	sem_end(t_infos *infos);

#endif
