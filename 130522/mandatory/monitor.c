/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->check);
			if (check_number_of_eat(data))
				return (1);
			if (time_stamp(data) - data->philo[i].time_of_last_eat > \
															data->time_to_die)
			{
				data->finish_flag = 1;
				pthread_mutex_unlock(&data->check);
				print_status(&data->philo[i], "died");
				pthread_mutex_lock(&data->check);
				return (1);
			}
			pthread_mutex_unlock(&data->check);
			i++;
		}
		custom_usleep(1);
	}
	return (0);
}
