/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:18:04 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 23:29:37 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int ms, t_data *data)
{
	long int	time;

	time = get_time();
	while (data->died == 0)
	{
		if (time_diff(time, get_time()) >= ms)
			break ;
		usleep(50);
	}
}

void	update_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->all_ate_mutex);
	data->all_ate = 1;
	pthread_mutex_unlock(&data->all_ate_mutex);
}

void	update_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->died = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

void	print(t_data *data, int philo_id, char *str)
{
	pthread_mutex_lock(&data->writing_mutex);
	if (data->died == 0)
		printf("%lld: Philo n'%d %s\n",
			get_time() - data->first_timestamp, philo_id, str);
	pthread_mutex_unlock(&data->writing_mutex);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}
