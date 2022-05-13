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

static int	philo_exit(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
	if (data)
		free(data);
	return (1);
}

static int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_unlock(&data->fork[i]);
		if (pthread_mutex_destroy(&data->fork[i]))
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->check))
		return (1);
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
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (philo_error("not allocation for data"));
	if (validation(argc, argv))
		return (philo_exit(data));
	if (initialization(argc, argv, data, &time))
		return (philo_exit(data));
	if (gettimeofday(&time.tv1, NULL))
		return (philo_exit(data));
	if (start_simulation(data))
		return (philo_exit(data));
	if (monitor(data))
	{
		if (destroy_mutexes(data))
			return (philo_exit(data));
	}
	philo_exit(data);
	return (0);
}
