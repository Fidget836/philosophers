/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:03:05 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 23:32:01 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print(data, philo->id, "has taken a fork");
	print(data, philo->id, "is eating");
	update_last_meal_time(philo);
	ft_usleep(data->t_eat, data);
	update_x_ate(philo);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	*thread_routine(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	update_last_meal_time(philo);
	shift_philo(philo, data);
	while (data->died == 0)
	{
		ft_eat(philo);
		if (check_all_ate(data) == 1)
		{
			pthread_mutex_unlock(&data->all_ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->all_ate_mutex);
		ft_sleep(philo);
		if (check_all_ate(data) == 1)
		{
			pthread_mutex_unlock(&data->all_ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->all_ate_mutex);
	}
	return (NULL);
}

int	check_death3(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->nb_eat != -1 && i <= data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].x_ate_mutex);
		if (philo[i].x_ate >= data->nb_eat)
		{
			pthread_mutex_unlock(&philo[i].x_ate_mutex);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&philo[i].x_ate_mutex);
			break ;
		}
	}
	if (i == data->nb_philo)
	{
		update_all_ate(data);
		return (2);
	}
	return (0);
}

int	check_death2(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo && data->died == 0)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if ((long long)get_time() - philo[i].t_last_meal
			>= (long long)data->t_death)
		{
			print(data, philo[i].id, "died");
			update_dead(data);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	if (data->died == 1)
		return (1);
	return (0);
}

void	*check_death(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	usleep(data->t_death / 2);
	while (data->all_ate == 0)
	{
		if (check_death2(data, philo) == 1)
			break ;
		if (check_death3(data, philo) == 2)
			update_all_ate(data);
	}
	return (NULL);
}
