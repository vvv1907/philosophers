/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
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

void	*monitor(void *argument)
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
