/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:03:27 by sasano            #+#    #+#             */
/*   Updated: 2024/09/20 23:07:40 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


// typedef struct args
// {
   
// }   t_args;

typedef struct s_philo
{
    int				philo_id;
    int             philo_status;
    int             num_of_philosophers;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				num_of_times_each_philosopher_must_eat;
    int             goal_reached_count;
    int	            last_eat_time;
    int             first_take_fork;
    int             second_take_fork;
    int				*forks;
    pthread_mutex_t	*fork_mutexs; 
    pthread_mutex_t	*status_mutex;
}	t_philo;


void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(char const *str);
int					ft_atoi(const char *str);
t_philo             *init_philos(int argc, char *argv[]);
int                 init_forks(t_philo *philos);
void                *routine(void *arguments);
int                take_fork(t_philo *philo);
int                release_fork(t_philo *philo);
int                 check_philos_death(t_philo *philos);
int                 check_goal_reached(t_philo *philos);
int finish_simu(t_philo *philos, pthread_t *threads);
int	                get_time(void);
void                free_philos(t_philo *philos);
int                 error(char *str);

#endif