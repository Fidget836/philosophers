/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:03:13 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 23:39:42 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					x_ate;
	int					left_fork;
	int					right_fork;
	long long			t_last_meal;
	struct s_data		*data;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		x_ate_mutex;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					t_death;
	int					t_eat;
	int					t_sleep;
	int					all_ate;
	int					died;
	int					nb_eat;
	long long			first_timestamp;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		all_ate_mutex;
	pthread_mutex_t		mut_nb_philos;
	pthread_t			thread_dead;
	t_philo				philosophers[250];
}	t_data;

/**********************USEFUL*FUNCTIONS********************/
int				ft_isdigit(int c);
int				ft_strlen(const char *s);
int				ft_iswhitespace(char c);
int				ft_atoi(const char *nptr);
char			*ft_strdup(const char *s);
int				ft_len(long int n);
char			*ft_itoa(int n);

/***************************ROUTINE*************************/
int				start_thread(t_data *data);
void			*thread_routine(void *philo_arg);
void			*check_death(void *philo_arg);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);

/***************************COMMAND*************************/
unsigned long	get_time(void);
void			ft_usleep(int ms, t_data *data);
int				isdead(t_philo *philo, int nb);
void			print(t_data *data, int philo_id, char *str);
int				init_data_global(t_data *data, int argc, char **argv);
void			init_data_philo(t_data *data);
int				init_mutex(t_data *data);
void			ft_sleep(t_philo *philo);
long long		time_diff(long long i, long long time);
void			shift_philo(t_philo *philo, t_data *data);

/***************************UPDATE&CHECK*************************/
void			update_all_ate(t_data *data);
void			update_dead(t_data *data);
void			update_last_meal_time(t_philo *philo);
void			update_x_ate(t_philo *philo);
int				check_all_ate(t_data *data);
#endif
