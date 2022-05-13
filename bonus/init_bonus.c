/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

int	data_init(int argc, char **argv, t_data *data, t_time *time)
{
	data->time = time;
	data->time_of_last_eat = 0;
	data->id = 0;
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
		data->number_of_eat = philo_atoi(argv[5]);
		if (data->number_of_eat < 0)
			return (1);
	}
	else
		data->number_of_eat = -1;
	return (0);
}

int	semaphores_init(t_data *data)
{
	sem_unlink("/check");
	sem_unlink("/fork");
	sem_unlink("/stop");
	sem_unlink("/eat");
	data->check = sem_open("/check", O_CREAT, S_IRWXU, 1);
	if (data->check == SEM_FAILED)
		return (1);
	data->fork = sem_open("/fork", O_CREAT, S_IRWXU, data->number_of_philo);
	if (data->fork == SEM_FAILED)
		return (1);
	data->stop = sem_open("/stop", O_CREAT, S_IRWXU, 0);
	if (data->stop == SEM_FAILED)
		return (1);
	data->eat = sem_open("/eat", O_CREAT, S_IRWXU, 0);
	if (data->eat == SEM_FAILED)
		return (1);
	return (0);
}
