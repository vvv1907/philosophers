/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:05 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:39:08 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->finish_flag || philo->number_of_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
	if (philo->max_id)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->finish_flag || philo->number_of_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		return ;
	}
	philo->time_of_last_eat = time_stamp(philo->data);
	philo->number_of_eat--;
	pthread_mutex_unlock(&philo->data->check);
	print_status(philo, "is eating");
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleeping(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->finish_flag || philo->number_of_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
	print_status(philo, "is sleeping");
	custom_usleep(philo->data->time_to_sleep);
}

static void	thinking(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->finish_flag || philo->number_of_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
	print_status(philo, "is thinking");
}

void	*processing(void *argument)
{
	t_philo	*philo;

	philo = argument;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(500);
	}
	return (NULL);
}
