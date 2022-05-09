/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&data->checker);
	if (pthread_mutex_destroy(&data->checker))
		return (1);
	pthread_mutex_unlock(&data->printer);
	if (pthread_mutex_destroy(&data->printer))
		return (1);
	pthread_mutex_unlock(&data->timer);
	if (pthread_mutex_destroy(&data->timer))
		return (1);
	return (0);
}

static int	check_number_of_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (data->philo[i].number_of_eat != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->checker);
			if (check_number_of_eat(data))
				return (1);
			if (time_stamp(data) - data->philo[i].time_of_last_eat > \
															data->time_to_die)
			{
				data->finish_flag = 1;
				print_status(&data->philo[i], "died");
				return (2);
			}
			pthread_mutex_unlock(&data->checker);
			i++;
		}
		custom_usleep(1);
	}
	return (0);
}

static int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
												processing, &data->philo[i]))
			return (philo_error("thread was not created"));
		if (pthread_detach(data->philo[i].thread))
			return (philo_error("thread was not detached"));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_time	time;
	t_data	data;

	if (validation(argc, argv))
		return (5);
	if (initialization(argc, argv, &data, &time))
		return (6);
	if (gettimeofday(&time.tv1, NULL))
		return (7);
	if (start_simulation(&data))
		return (8);
	if (monitor(&data))
	{
		if (destroy_mutexes(&data))
			return (9);
	}
	return (0);
}
