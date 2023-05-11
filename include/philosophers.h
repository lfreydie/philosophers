/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/11 15:45:56 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
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
	int			last_meal;
	int			nb_meal;
	t_infos		*infos;
}	t_philo;

typedef struct s_infos
{
	t_philo			*tab_philo;
	pthread_t		super;
	int				nb_philo;
	int				t_start;
	int				t_die;
	pthread_mutex_t	check_dead;
	int				dead;
	int				t_eat;
	int				t_sleep;
	int				nb_cycle;
	pthread_mutex_t	write;
	pthread_mutex_t	*tab_fork;
}	t_infos;

# define ERR_ARG "arguments invalid\n"
# define ERR_MAL "erreur malloc\n"

//	INIT
t_infos	*ft_init(int ac, char **av);
void	get_infos(t_infos *infos, int ac, char **av);
void	fork_set(t_infos *infos);
void	philo_set(t_infos *infos);

//	PHILO
void	ft_launch(void *philo);
void	ft_supervisor(void *data);

//	ACTIVITIES
void	ft_take_fork(pthread_mutex_t fork, t_philo *perso);
void	ft_eat(t_philo *perso);
void	ft_think(t_philo *perso);
void	ft_sleep(t_philo *perso);

//	TIME
int		get_time(t_infos *infos);
int		running_time(t_infos *infos);
void	ft_waiting(t_philo *perso, int time);

//	UTILS
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);

//	EXIT
void	ft_exit(t_infos *infos, char *msg);
void	free_infos(t_infos *infos);

#endif
