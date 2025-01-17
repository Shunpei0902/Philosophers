/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:02:46 by sasano            #+#    #+#             */
/*   Updated: 2025/01/17 14:16:46 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_die_and_goal(t_philo *philos)
{
	if (philos->num_of_times_each_philosopher_must_eat != -1)
	{
		while (!check_goal_reached(philos))
			;
	}
	return ;
}

int	start_routine(t_philo *philos, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < philos->num_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, routine, (void *)&philos[i]))
			return (1);
		usleep(100);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	pthread_t	*threads;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) == 0)
		return (error("invalid arguments"));
	philos = init_philos(argc, argv);
	if (!philos)
		return (error("init_philos error"));
	if (init_forks(philos) || init_simu_state(philos))
		return (error("init error"));
	threads = (pthread_t *)malloc(sizeof(pthread_t)
			* philos->num_of_philosophers);
	if (!threads)
	{
		finish_simu(philos, NULL);
		return (error("malloc error"));
	}
	if (start_routine(philos, threads))
	{
		finish_simu(philos, threads);
		return (error("start_routine error"));
	}
	check_die_and_goal(philos);
	finish_simu(philos, threads);
	return (0);
}
