/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    main.c                                             :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: hcolumbu <hcolumbu@student.21-school.ru>   +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2022/04/23 08:00:00 by hcolumbu          #+#    #+#              */
/*    Updated: 2022/04/23 10:40:56 by hcolumbu         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

int             mails = 0;
pthread_mutex_t mutex;

typedef struct  s_philo
{
	int	        number_of_philosophers;
	int	        time_to_die;
	int	        time_to_eat;
	int	        time_to_sleep;
	int	        number_of_times_each_philosopher_must_eat;   
}               t_philo;

int    philo_error(char *str)
{
    int i;

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

static int philo_atoi(char *str)
{
    int      i;
    long int result;

    i = 0;
    result = 0;
    if (str[i] == '+')
        i++;
    while (str[i])
    {
        result = result * 10 + ((int)str[i] - 48);
        i++;
        if (result > 2147483647 || i > 11)
            return (philo_error("argument must not be larger than an integer"));            
    }
    return (result);
}

static int init(int argc, char **argv, t_philo *data)
{
    data->number_of_philosophers = philo_atoi(argv[1]);
    if (data->number_of_philosophers < 0)
        return (-1);
    data->time_to_die = philo_atoi(argv[2]);
    if (data->time_to_die < 0)
        return (-1);
    data->time_to_eat = philo_atoi(argv[3]);
    if (data->time_to_eat < 0)
        return (-1);
    data->time_to_sleep = philo_atoi(argv[4]);
    if (data->time_to_sleep < 0)
        return (-1);
    if (argc == 6)
    {
        data->number_of_times_each_philosopher_must_eat = philo_atoi(argv[5]);
        if (data->number_of_times_each_philosopher_must_eat < 0)
            return (-1);
    }
    else
        data->number_of_times_each_philosopher_must_eat = 0;
    return (0);
}

static int  validation(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
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

void    *philo_action()
{
    for (int i = 0; i < 1000000; i++) 
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_philo         data;
    pthread_t       philosopher[8];
    int             i;
    struct timeval	now;
    
    i = 0;
    if (argc < 5 || argc > 6)
       return (philo_error("wrong arguments number"));
    else
    {
        if (validation(argc, argv))
           return (-1);
        if (!init(argc, argv, &data))
        {
            gettimeofday(&now, NULL);
            usleep(3000000);
            printf("1st = %d\n", data.number_of_philosophers);
            printf("2nd = %d\n", data.time_to_die);
            printf("3rd = %d\n", data.time_to_eat);
            printf("4th = %d\n", data.time_to_sleep);
            printf("5th = %d\n", data.number_of_times_each_philosopher_must_eat);
            pthread_mutex_init(&mutex, NULL);
            while (i < data.number_of_philosophers)
            {
                pthread_create(philosopher + i, NULL, philo_action, NULL);
                i++;
                printf("Philosopher number %d was created\n", i);
            }
            i = 0;
            while (i < data.number_of_philosophers)
            {
                pthread_join(philosopher[i], NULL);
                i++;
                printf("Philosopher number %d was joined\n", i);
            }
        }
        else
            return (-1);
    }
    printf("Number of mails: %d\n", mails);
    return (0);
}
