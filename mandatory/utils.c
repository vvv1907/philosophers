/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_error(char *str)
{
	int	i;

	i = 0;
	write(2, "Error: ", 7);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (-1);
}

int	validation(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (philo_error("wrong arguments number"));
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		if (!argv[i][j])
			return (philo_error("argument must be a positive number"));
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (philo_error("argument must be a positive number"));
			j++;
		}
		i++;
	}
	return (0);
}

long	time_stamp(t_data *data)
{
	long	result;

	pthread_mutex_lock(&data->timer);
	gettimeofday(&data->time->tv2, NULL);
	data->time->dtv.tv_sec = data->time->tv2.tv_sec - \
								data->time->tv1.tv_sec;
	data->time->dtv.tv_usec = data->time->tv2.tv_usec - \
								data->time->tv1.tv_usec;
	result = data->time->dtv.tv_sec * 1000 + data->time->dtv.tv_usec / 1000;
	pthread_mutex_unlock(&data->timer);
	return (result);
}

void	custom_usleep(int ms)
{
	t_time	custom;

	gettimeofday(&custom.tv1, NULL);
	gettimeofday(&custom.tv2, NULL);
	while (ms > ((custom.tv2.tv_sec - custom.tv1.tv_sec) * 1000 + \
					(custom.tv2.tv_usec - custom.tv1.tv_usec) / 1000))
	{
		usleep(10);
		gettimeofday(&custom.tv2, NULL);
	}
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->printer);
	printf("%ld %d %s\n", time_stamp(philo->data), philo->id, status);
	pthread_mutex_unlock(&philo->data->printer);
}
