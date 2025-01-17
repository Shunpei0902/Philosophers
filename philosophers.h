/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:03:27 by sasano            #+#    #+#             */
/*   Updated: 2025/01/17 11:46:08 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	int				*simu_state;
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philosopher_must_eat;
	int				goal_reached_count;
	int				last_eat_time;
	int				first_take_fork;
	int				second_take_fork;
	int				*forks;
	int				take_forks;
	pthread_mutex_t	*fork_mutexs;
	pthread_mutex_t	*state_mutex;
}					t_philo;

void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(char const *str);
int					ft_atoi(const char *str);
void				ft_bzero(void *dest, size_t n);
void				*ft_calloc(size_t n, size_t size);
t_philo				*init_philos(int argc, char *argv[]);
int					init_forks(t_philo *philos);
int					init_simu_state(t_philo *philos);
void				*routine(void *arguments);
void				take_fork(t_philo *philo);
void				release_fork(t_philo *philo);
void				check_die(t_philo *philo);
int					get_time(void);
void				ft_log(int time, char *message, t_philo *philo);
int					check_goal_reached(t_philo *philos);
int					finish_simu(t_philo *philos, pthread_t *threads);
void				free_philos(t_philo *philos);
int					error(char *str);

#endif