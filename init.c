/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:17:22 by sasano            #+#    #+#             */
/*   Updated: 2025/01/10 13:57:42 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_simu_state(t_philo *philos)
{
	int	i;
	int	*simu_state;

	i = -1;
	simu_state = (int *)malloc(sizeof(int));
	philos->state_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!simu_state || !philos->state_mutex)
	{
		if (!philos->state_mutex)
			free(simu_state);
		free(philos->forks);
		free(philos->fork_mutexs);
		free(philos);
		return (1);
	}
	*simu_state = 1;
	pthread_mutex_init(philos->state_mutex, NULL);
	while (++i < philos->num_of_philosophers)
	{
		philos[i].simu_state = simu_state;
		philos[i].state_mutex = philos->state_mutex;
	}
	return (0);
}

int	init_forks(t_philo *philos)
{
	int	i;

	philos->forks = (int *)malloc(sizeof(int) * philos->num_of_philosophers);
	philos->fork_mutexs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philos->num_of_philosophers);
	if (!philos->forks || !philos->fork_mutexs)
	{
		if (!philos->fork_mutexs)
			free(philos->forks);
		free(philos);
		return (error("malloc error"));
	}
	i = -1;
	while (++i < philos->num_of_philosophers)
	{
		pthread_mutex_init(&philos->fork_mutexs[i], NULL);
		philos->forks[i] = 1;
		philos[i].forks = philos->forks;
		philos[i].fork_mutexs = philos->fork_mutexs;
	}
	return (0);
}

void	set_args(t_philo *philos, int i, int argc, char *argv[])
{
	philos[i].philo_id = i + 1;
	philos[i].num_of_philosophers = ft_atoi(argv[1]);
	philos[i].time_to_die = ft_atoi(argv[2]);
	philos[i].time_to_eat = ft_atoi(argv[3]);
	philos[i].time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos[i].num_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philos[i].num_of_times_each_philosopher_must_eat = -1;
	philos[i].goal_reached_count = philos[i].num_of_times_each_philosopher_must_eat;
}

t_philo	*init_philos(int argc, char *argv[])
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		set_args(philos, i, argc, argv);
		// 偶数・奇数でフォークを取る順番を変更
		if (i % 2 == 0)
		{
			philos[i].first_take_fork = i;
			philos[i].second_take_fork = i - 1;
			if (i == 0)
				philos[i].second_take_fork = philos->num_of_philosophers - 1;
		}
		else
		{
			philos[i].first_take_fork = i - 1;
			philos[i].second_take_fork = i;
		}
	}
	return (philos);
}
