/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:02:46 by sasano            #+#    #+#             */
/*   Updated: 2024/09/21 00:02:21 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_die_and_goal(t_philo *philos)
{
	int i;

	if (philos->num_of_times_each_philosopher_must_eat == -1)
	{
		// 死亡者の監視
		while(!check_philos_death(philos))
			;
	}
	else 
	{
		// 死亡者の監視 && 目標達成者の監視
		while(!check_goal_reached(philos) && !check_philos_death(philos))
			;
	}
	i = -1;
	// printf("finish simulation\n");
	while (++i < philos->num_of_philosophers)
	// {
		// pthread_mutex_lock(philos[i].status_mutex);
		philos[i].philo_status = 0;
		// pthread_mutex_unlock(philos[i].status_mutex);
	// }
	return ;
}

int start_routine(t_philo *philos, pthread_t *threads)
{
	int i;

	i = -1;
	while (++i < philos->num_of_philosophers)
	{
		if (i % 2 == 0)
			usleep(3000);
		if (pthread_create(&threads[i], NULL, routine, (void *)&philos[i]))
			return (error("start_routine error"));
	}
	return (0);
}


int	main(int argc, char *argv[])
{
	// printf("start simulation\n");
	t_philo		*philos;
	pthread_t	*threads;

	// 入力チェック&args構造体の作成
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) == 0)
		return (error("invalid arguments"));
	// 哲学者構造体の作成
	philos = init_philos(argc, argv);
	if (!philos)
		return (error("init_philos error"));
	// フォークの作成
	if (init_forks(philos))
		return (error("init_forks error"));
	// スレッドの作成
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos->num_of_philosophers);
	if (!threads)
		return (error("malloc error"));
	if (start_routine(philos, threads))
		return (error("start_routine error"));
	// シミュレーションの終了待ち
	check_die_and_goal(philos);
	finish_simu(philos, threads);
	return (0);
}