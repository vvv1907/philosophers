/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + ((int)str[i] - 48);
		i++;
		if (result > 2147483647 || i > 11)
			return (philo_error("argument mustn't be larger than an integer"));
	}
	return (result);
}

static int	data_init(int argc, char **argv, t_data *data, t_time *time)
{
	data->time = time;
	data->finish_flag = 0;
	data->number_of_philo = philo_atoi(argv[1]);
	if (data->number_of_philo <= 0)
		return (1);
	data->time_to_die = philo_atoi(argv[2]);
	if (data->time_to_die < 0)
		return (1);
	data->time_to_eat = philo_atoi(argv[3]);
	if (data->time_to_eat < 0)
		return (1);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (data->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		data->optional_argument = philo_atoi(argv[5]);
		if (data->optional_argument < 0)
			return (1);
	}
	else
		data->optional_argument = -1;
	return (0);
}

static int	mutexes_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->fork)
		return (philo_error("not allocation for mutexes"));
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (philo_error("fork_mutex was not initialized"));
		i++;
	}
	if (pthread_mutex_init(&data->check, NULL))
		return (philo_error("check_mutex was not initialized"));
	return (0);
}

static int	philo_init(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (philo_error("not allocation for philo"));
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].number_of_eat = data->optional_argument;
		data->philo[i].time_of_last_eat = 0;
		data->philo[i].max_id = 0;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->fork[i];
		if (i == 0)
			data->philo[i].right_fork = &data->fork[data->number_of_philo - 1];
		else
			data->philo[i].right_fork = &data->fork[i - 1];
		i++;
	}
	data->philo[data->number_of_philo - 1].max_id = 1;
	return (0);
}

int	initialization(int argc, char **argv, t_data *data, t_time *time)
{
	if (data_init(argc, argv, data, time))
		return (1);
	if (mutexes_init(data))
		return (1);
	if (philo_init(data))
		return (1);
	return (0);
}
