/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	free_data(t_data *data)
{
	if (data)
		free(data);
	return (1);
}

static int	unlink_and_free(t_data *data)
{
	if (sem_unlink("/eat"))
		philo_error("not unlink /eat");
	if (sem_unlink("/stop"))
		philo_error("not unlink /stop");
	if (sem_unlink("/fork"))
		philo_error("not unlink /fork");
	if (sem_unlink("/check"))
		philo_error("not unlink /check");
	if (data->pid)
		free(data->pid);
	if (data)
		free(data);
	return (1);
}

static int	start_simulation(t_data *data)
{
	int	id;
	int	i;

	i = 0;
	id = 1;
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->number_of_philo);
	if (!data->pid)
		return (philo_error("not allocation for data->pid"));
	while (i < data->number_of_philo)
	{
		data->id = i + 1;
		if (id != 0)
		{
			id = fork();
			if (id == -1)
				return (philo_error("child process was not created"));
			else if (id == 0)
				processing(data);
			else
				data->pid[i] = id;
		}
		i++;
	}
	return (0);
}

static int	finish_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->number_of_eat != -1)
	{
		while (i < data->number_of_philo)
		{
			sem_wait(data->eat);
			i++;
		}
		while (--i >= 0)
		{
			if (kill(data->pid[i], SIGTERM))
				return (1);
		}
		return (0);
	}
	sem_wait(data->stop);
	while (i < data->number_of_philo)
	{
		if (kill(data->pid[i], SIGTERM))
			return (1);
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
		return (free_data(data));
	if (data_init(argc, argv, data, &time))
		return (free_data(data));
	if (semaphores_init(data))
		return (unlink_and_free(data));
	if (gettimeofday(&time.tv1, NULL))
		return (unlink_and_free(data));
	if (start_simulation(data))
		return (unlink_and_free(data));
	if (finish_simulation(data))
		return (unlink_and_free(data));
	unlink_and_free(data);
	return (0);
}
