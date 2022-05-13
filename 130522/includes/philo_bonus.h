/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:53:27 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/04/27 19:14:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_time
{
	struct timeval	tv1;
	struct timeval	tv2;
	struct timeval	dtv;
}					t_time;

typedef struct s_data
{
	int				id;
	long			time_of_last_eat;
	pthread_t		thread;
	pid_t			*pid;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				finish_flag;
	sem_t			*check;
	sem_t			*fork;
	sem_t			*stop;
	sem_t			*eat;
	struct s_time	*time;
}					t_data;

int		data_init(int argc, char **argv, t_data *data, t_time *time);
int		validation(int argc, char **argv);
int		semaphores_init(t_data *data);
int		processing(t_data *data);
int		philo_error(char *str);
long	time_stamp(t_data *data);
void	custom_usleep(int ms);
void	print_status(t_data *data, char *status);
// void	*monitor(void *argument);

#endif
