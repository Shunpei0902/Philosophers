/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:13:46 by sasano            #+#    #+#             */
/*   Updated: 2024/09/21 00:03:32 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_philos_death(t_philo *philos)
{
    int i;

    i = -1;
    while (++i < philos->num_of_philosophers)
    {
        if (philos[i].philo_status)
        {
            if (get_time() > philos[i].last_eat_time + philos[i].time_to_die)
            {
                printf("%d %d is dead\n", get_time(), philos[i].philo_id);
                return (1);
            }
        }
    }
    return (0);
}

int check_goal_reached(t_philo *philos)
{
    int i;

    i = -1;
    while (++i < philos->num_of_philosophers)
    {
        if (philos[i].goal_reached_count == 0)
            return (1);
    }
    return (0);
}

int finish_simu(t_philo *philos, pthread_t *threads)
{
    int i;

    i = -1;
    while (++i < philos->num_of_philosophers)
        pthread_mutex_destroy(&(philos->fork_mutexs[i]));
    while (++i < philos->num_of_philosophers)
    {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free_philos(philos);
    return (0);
}

// ミリ秒単位で取得
int	get_time(void)
{
	struct timeval	time;
	static int		t = 0;

	if (gettimeofday(&time, NULL) == -1)
        return (-1);
	if (t == 0)
		t = time.tv_sec;
	return (((time.tv_sec - t) * 1000) + (time.tv_usec / 1000));
}

void free_philos(t_philo *philos)
{
    int i;

    i = -1;
    while (++i < philos->num_of_philosophers)
    {
        pthread_mutex_destroy(&(philos->fork_mutexs[i]));
        pthread_mutex_destroy(philos[i].status_mutex);
    }
    free(philos->forks);
    free(philos->fork_mutexs);
    free(philos->status_mutex);
    free(philos);
}

int  error(char *str)
{
    ft_putstr_fd(str, 2);
    return (1);
}