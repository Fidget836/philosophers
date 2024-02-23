/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:18:08 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 23:32:11 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->all_ate_mutex);
	if (data->all_ate == 1)
		return (1);
	else
		return (0);
}

long long	time_diff(long long i, long long time)
{
	return (time - i);
}

void	update_x_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->x_ate_mutex);
	philo->x_ate++;
	pthread_mutex_unlock(&philo->x_ate_mutex);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print(data, philo->id, " is sleeping");
	ft_usleep(data->t_sleep, data);
	print(data, philo->id, "is thinking");
}

void	shift_philo(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat / 10, data);
}
