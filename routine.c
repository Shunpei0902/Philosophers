/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:53:39 by sasano            #+#    #+#             */
/*   Updated: 2024/09/20 23:56:07 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int action_think(t_philo *philo)
{
    if (!philo->philo_status)
        return (1);
    printf("%d %d is thinking\n", get_time(), philo->philo_id);
    return (0);
}

int action_sleep(t_philo *philo)
{
    int start_time;

    if (philo->philo_status == 0)
        return (1);
    start_time = get_time();
    printf("%d %d is sleeping\n", start_time, philo->philo_id);
    while(philo->philo_status != 0 && get_time() < start_time + philo->time_to_sleep)
        ;
    return (action_think(philo));
}

int action_eat(t_philo *philo)
{
    int start_time;

    if (philo->philo_status == 0 || take_fork(philo))
        return (1);
    start_time = get_time();
    printf("%d %d is eating\n", start_time, philo->philo_id);
    philo->last_eat_time = start_time;
    while(philo->philo_status != 0 && get_time() - philo->last_eat_time < philo->time_to_eat)
        ;
    if (philo->philo_status == 0 ||release_fork(philo))
        return (1);
    return (action_sleep(philo));
}

// int action(t_philo *philo)
// {
//     int status;

//     pthread_mutex_lock(philo->status_mutex);
//     status = philo->philo_status;
//     pthread_mutex_unlock(philo->status_mutex);
//     if (status == 1 && action_eat(philo))
//         return (1);
//     else if (status == 2 && action_sleep(philo))
//         return (1);
//     else if (status == 3 && action_think(philo))
//         return (1);
//     return (0);
// }

void *routine(void *arguments)
{
    t_philo *philo;
    
    philo = (t_philo *)arguments;
    philo->last_eat_time = get_time();
    philo->philo_status = 1;
    while (!action_eat(philo))
    ;
    // free_philos(philo);
    pthread_mutex_destroy(philo->fork_mutexs);
    printf("%d %d finish routine\n", get_time(), philo->philo_id);
    return (NULL);
}