/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:22:50 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/12 13:33:39 by lfreydie         ###   ########.fr       */
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
	pthread_t		thread;
	int				id;
	int				r_fork;
	int				l_fork;
	int				last_meal;
	int				nb_meal;
	struct s_infos	*infos;
}	t_philo;

typedef struct s_infos
{
	t_philo			*tab_philo;
	pthread_mutex_t	*tab_fork;
	pthread_mutex_t	write;
	pthread_mutex_t	check_dead;
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
# define ERR_MAL "erreur malloc\n"

//	INIT
t_infos	*ft_init(int ac, char **av);
void	get_infos(t_infos *infos, int ac, char **av);
void	fork_set(t_infos *infos);
void	philo_set(t_infos *infos);

//	PHILO
void	*ft_launch(void *philo);
void	ft_supervisor(void *data);

//	ACTIVITIES
int		ft_take_forks(t_philo *perso);
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
int		check_dead(t_philo perso);
int		check_dead_all(t_infos *infos);

//	EXIT
void	ft_exit(t_infos *infos, char *msg);
void	free_infos(t_infos *infos);

#endif
