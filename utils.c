#include "philo.h"

size_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printf_time(t_philo *philo, char *str, char *color)
{
	long long	time;

	pthread_mutex_lock(&philo->data->mutex_for_died);
	if (philo->data->died || philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->mutex_for_died);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_for_died);
	time = time_now() - philo->data->start;
	pthread_mutex_lock(&philo->data->mutex_for_print);
	pthread_mutex_lock(&philo->data->mutex_for_died);
	if (philo->data->died || philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->mutex_for_died);
		pthread_mutex_unlock(&philo->data->mutex_for_print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_for_died);
	printf("%s[%lld] %d %s%s\n", color, time, philo->id, str, RESET);
	pthread_mutex_unlock(&philo->data->mutex_for_print);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_for_check_meal);
	pthread_mutex_destroy(&data->mutex_for_eat);
	pthread_mutex_destroy(&data->mutex_for_died);
	pthread_mutex_destroy(&data->mutex_for_print);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

void	data_init(t_data *data)
{
	data->done = 0;
	data->full = 0;
	data->died = 0;
	pthread_mutex_init(&data->mutex_for_check_meal, NULL);
	pthread_mutex_init(&data->mutex_for_eat, NULL);
	pthread_mutex_init(&data->mutex_for_died, NULL);
	pthread_mutex_init(&data->mutex_for_print, NULL);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	sign = 1;
	number = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
