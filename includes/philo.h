/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:53:27 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:14:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

# define NUMBER 201

typedef struct s_time
{
	struct timeval	tv1;
	struct timeval	tv2;
	struct timeval	dtv;
}					t_time;

typedef struct s_philo
{
	int				id;
	int				max_id;
	int				number_of_eat;
	long			time_of_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional_argument;
	int				finish_flag;
	pthread_mutex_t	printer;
	pthread_mutex_t	checker;
	pthread_mutex_t	timer;
	pthread_mutex_t	fork[NUMBER];
	t_philo			philo[NUMBER];
	struct s_time	*time;
}					t_data;

int		initialization(int argc, char **argv, t_data *data, t_time *time);
int		validation(int argc, char **argv);
int		philo_error(char *str);
long	time_stamp(t_data *data);
void	custom_usleep(int ms);
void	print_status(t_philo *philo, char *status);
void	*processing(void *argument);

#endif
