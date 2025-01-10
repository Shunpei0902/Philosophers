/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:02:46 by sasano            #+#    #+#             */
/*   Updated: 2025/01/10 14:51:04 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_die_and_goal(t_philo *philos)
{
	// int i;
	// if (philos->num_of_times_each_philosopher_must_eat == -1)
	// {
	// 	// 死亡者の監視
	// 	while(!check_philos_death(philos))
	// 		;
	// }
	// else
	// {
	// 	// 死亡者の監視 && 目標達成者の監視
	// 	while(!check_goal_reached(philos) && !check_philos_death(philos))
	// 		;
	// }
	if (philos->num_of_times_each_philosopher_must_eat != -1)
	{
		// 目標達成者の監視
		while (!check_goal_reached(philos))
			;
	}
	// i = -1;
	// printf("finish simulation\n");
	// while (++i < philos->num_of_philosophers)
	// {
	// pthread_mutex_lock(philos[i].state_mutex);
	// pthread_mutex_unlock(philos[i].state_mutex);
	// }
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
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	pthread_t	*threads;

	// 入力チェック&args構造体の作成
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) == 0)
		return (error("invalid arguments"));
	// 哲学者構造体の作成
	philos = init_philos(argc, argv);
	if (!philos)
		return (error("init_philos error"));
	// フォークの作成とsimu_stateの初期化
	if (init_forks(philos) || init_simu_state(philos))
		return (error("init error"));
	// スレッドの作成
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
	// シミュレーションの終了待ち
	check_die_and_goal(philos);
	// wait_simu(threads);
	finish_simu(philos, threads);
	return (0);
}
