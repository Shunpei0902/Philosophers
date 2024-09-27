/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:31:30 by sasano            #+#    #+#             */
/*   Updated: 2024/09/20 23:57:16 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int take_fork(t_philo *philo)
{
    if (philo->philo_status == 0 || pthread_mutex_lock(&philo->fork_mutexs[philo->first_take_fork]) == -1)
        return (1);
    printf("%d %d has taken a fork\n", get_time(), philo->philo_id);
    if (philo->philo_status == 0 || philo->num_of_philosophers == 1 || pthread_mutex_lock(&philo->fork_mutexs[philo->second_take_fork]) == -1)
    {
        pthread_mutex_unlock(&philo->fork_mutexs[philo->first_take_fork]);
        return (1);
    }
    printf("%d %d has taken a fork\n", get_time(), philo->philo_id);
    return (0);
}

int release_fork(t_philo *philo)
{
    if (philo->philo_status == 0 || pthread_mutex_unlock(&philo->fork_mutexs[philo->first_take_fork]) == -1)
        return (1); 
    printf("%d %d has release a fork\n", get_time(), philo->philo_id);
    if (philo->philo_status == 0 || pthread_mutex_unlock(&philo->fork_mutexs[philo->second_take_fork]) == -1)
    {
        pthread_mutex_lock(&philo->fork_mutexs[philo->first_take_fork]);
        return (1);
    }
    printf("%d %d has release a fork\n", get_time(), philo->philo_id);
    return (0);
}