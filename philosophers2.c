/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:03:01 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 08:03:02 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data_global(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->t_death = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->all_ate = 0;
	data->died = 0;
	if (argc == 6)
	{
		data->nb_eat = ft_atoi(argv[5]);
		if (data->nb_eat <= 0)
			return (1);
	}
	else
		data->nb_eat = -1;
	return (0);
}

void	init_data_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].x_ate = 0;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->nb_philo;
		data->philosophers[i].t_last_meal = 0;
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL);
		pthread_mutex_init(&data->philosophers[i].x_ate_mutex, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
	}
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->writing_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->all_ate_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->mut_nb_philos, NULL))
		return (1);
	return (0);
}
