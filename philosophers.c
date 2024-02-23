/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 07:24:56 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 08:02:40 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

int	start_thread(t_data *data)
{
	int				i;

	data->first_timestamp = get_time();
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philosophers[i].thread_id,
				NULL, &thread_routine, &data->philosophers[i]))
			return (1);
	}
	if (pthread_create(&data->thread_dead,
			NULL, &check_death, &data->philosophers))
		return (1);
	return (0);
}

int	join_thread(t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philosophers[i].thread_id, NULL))
			return (1);
	}
	if (pthread_join(data->thread_dead, NULL))
		return (1);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
		pthread_mutex_destroy(&data->philosophers[i].x_ate_mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->writing_mutex);
	return (0);
}

int	main2(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Not enough arguments !\n");
		return (1);
	}
	if (init_data_global(data, argc, argv) == 1)
	{
		printf("Error, philosophers must eat at least once !\n");
		return (1);
	}
	if (init_mutex(data) == 1)
	{
		printf("Error, init mutex!\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (main2(argc, argv, &data) == 1)
		return (1);
	if (data.nb_philo == 1)
	{
		data.first_timestamp = get_time();
		print(&data, 1, "has taken a fork");
		usleep(data.t_death * 1000);
		print(&data, 1, "is dead");
		return (0);
	}
	init_data_philo(&data);
	start_thread(&data);
	join_thread(&data);
	return (0);
}
