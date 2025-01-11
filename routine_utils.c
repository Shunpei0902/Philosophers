/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:31:30 by sasano            #+#    #+#             */
/*   Updated: 2025/01/10 17:04:11 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_philo *philo)
{
	if (*(philo->simu_state) == 0)
		return (0);
	pthread_mutex_lock(&philo->fork_mutexs[philo->first_take_fork]);
	if (philo->forks[philo->first_take_fork])
	{
		ft_log(get_time(), "has taken a fork", philo);
		philo->forks[philo->first_take_fork] = 0;
		philo->take_forks++;
	}
	pthread_mutex_unlock(&philo->fork_mutexs[philo->first_take_fork]);
	if (philo->num_of_philosophers == 1)
		return (philo->take_forks);
	pthread_mutex_lock(&philo->fork_mutexs[philo->second_take_fork]);
	if (philo->forks[philo->second_take_fork])
	{
		ft_log(get_time(), "has taken a fork", philo);
		philo->forks[philo->second_take_fork] = 0;
		philo->take_forks++;
	}
	pthread_mutex_unlock(&philo->fork_mutexs[philo->second_take_fork]);
	return (philo->take_forks);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutexs[philo->second_take_fork]);
	philo->forks[philo->second_take_fork] = 1;
	pthread_mutex_unlock(&philo->fork_mutexs[philo->second_take_fork]);
	pthread_mutex_lock(&philo->fork_mutexs[philo->first_take_fork]);
	philo->forks[philo->first_take_fork] = 1;
	pthread_mutex_unlock(&philo->fork_mutexs[philo->first_take_fork]);
	philo->take_forks = 0;
}

void	check_die(t_philo *philo)
{
	if (get_time() - philo->time_to_die > philo->last_eat_time)
	{
		ft_log(get_time(), "dead", philo);
		pthread_mutex_lock(philo->state_mutex);
		*(philo->simu_state) = 0;
		pthread_mutex_unlock(philo->state_mutex);
	}
}

void	ft_log(int time, char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	if (*(philo->simu_state))
		printf("%d %d %s\n", time, philo->philo_id, message);
	pthread_mutex_unlock(philo->state_mutex);
}
