/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:53:39 by sasano            #+#    #+#             */
/*   Updated: 2025/01/17 11:28:11 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	action_think(t_philo *philo)
{
	if (*(philo->simu_state) == 0)
		return (1);
	ft_log(get_time(), "is thinking", philo);
	return (0);
}

int	action_sleep(t_philo *philo)
{
	int	start_time;

	if (*(philo->simu_state) == 0)
		return (1);
	start_time = get_time();
	ft_log(get_time(), "is sleeping", philo);
	while (*(philo->simu_state) && get_time() < start_time
		+ philo->time_to_sleep)
		check_die(philo);
	return (action_think(philo));
}

int	action_eat(t_philo *philo)
{
	if (*(philo->simu_state) == 0)
		return (1);
	philo->take_forks = 0;
	while (*(philo->simu_state) && philo->take_forks < 2)
	{
		take_fork(philo);
		check_die(philo);
	}
	philo->last_eat_time = get_time();
	ft_log(get_time(), "is eating", philo);
	while (*(philo->simu_state) && get_time() < (philo->last_eat_time
			+ philo->time_to_eat))
		check_die(philo);
	release_fork(philo);
	philo->goal_reached_count--;
	return (action_sleep(philo));
}

void	*routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (philo->philo_id % 2)
		usleep(200);
	philo->last_eat_time = get_time();
	while (!action_eat(philo))
		;
	return (NULL);
}
