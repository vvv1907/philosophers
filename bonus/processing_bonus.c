/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	stop_monitor(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		sem_post(data->eat);
		i++;
	}
	sem_post(data->stop);
}

static void	*monitor(void *argument)
{
	t_data	*data;

	data = argument;
	while (1)
	{
		sem_wait(data->check);
		if (data->number_of_eat == 0)
		{
			sem_post(data->eat);
			sem_post(data->check);
			return (NULL);
		}
		if (time_stamp(data) - data->time_of_last_eat > data->time_to_die)
		{
			data->finish_flag = 1;
			printf("%ld %d %s\n", time_stamp(data), data->id, "died");
			stop_monitor(data);
			return (NULL);
		}
		sem_post(data->check);
		custom_usleep(1);
	}
	return (NULL);
}

int	processing(t_data *data)
{
	if (pthread_create(&data->thread, NULL, monitor, data))
		return (1);
	if (pthread_detach(data->thread))
		return (1);
	if (data->id % 2 == 0)
		usleep(500);
	while (data->number_of_eat != 0 || !data->finish_flag)
	{
		sem_wait(data->fork);
		print_status(data, "has taken a fork");
		sem_wait(data->fork);
		print_status(data, "has taken a fork");
		sem_wait(data->check);
		data->time_of_last_eat = time_stamp(data);
		data->number_of_eat--;
		sem_post(data->check);
		print_status(data, "is eating");
		custom_usleep(data->time_to_eat);
		sem_post(data->fork);
		sem_post(data->fork);
		print_status(data, "is sleeping");
		custom_usleep(data->time_to_sleep);
		print_status(data, "is thinking");
	}
	return (0);
}
