/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:13:46 by sasano            #+#    #+#             */
/*   Updated: 2025/01/10 17:21:12 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_goal_reached(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->num_of_philosophers)
	{
		if (philos[i].goal_reached_count > 0)
			return (0);
	}
	pthread_mutex_lock(philos->state_mutex);
	*(philos->simu_state) = 0;
	pthread_mutex_unlock(philos->state_mutex);
	return (1);
}

int	finish_simu(t_philo *philos, pthread_t *threads)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(philos->state_mutex);
	while (++i < philos->num_of_philosophers)
	{
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free_philos(philos);
	return (0);
}

int	get_time(void)
{
	struct timeval	time;
	static int		t;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	if (t == 0)
		t = time.tv_sec * 1000 + time.tv_usec / 1000;
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - t);
}

void	free_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->num_of_philosophers)
		pthread_mutex_destroy(&(philos->fork_mutexs[i]));
	free(philos->forks);
	free(philos->fork_mutexs);
	free(philos->state_mutex);
	free(philos);
}

int	error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
