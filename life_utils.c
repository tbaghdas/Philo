
#include "philo.h"

int	check_life(t_data *data)
{
	int	i;
	int	full_copy;

	i = 0;
	pthread_mutex_lock(&data->mutex_for_eat);
	full_copy = data->full;
	pthread_mutex_unlock(&data->mutex_for_eat);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_for_check_meal);
		if (((time_now() - data->philos[i].last_time_ate) > data->time_to_die)
			&& full_copy == 0)
		{
			printf_time(&data->philos[i], "died", RED);
			pthread_mutex_lock(&data->mutex_for_died);
			data->died = 1;
			pthread_mutex_unlock(&data->mutex_for_died);
			pthread_mutex_unlock(&data->mutex_for_check_meal);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex_for_check_meal);
		i++;
	}
	return (0);
}

int	done_eating(t_data *data)
{
	int	i;
	int	full;

	full = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_for_eat);
		if (data->philos[i].eaten >= data->eat_count)
		{
			full++;
		}
		pthread_mutex_unlock(&data->mutex_for_eat);
		i++;
	}
	if (full == data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_for_died);
		data->done = 1;
		pthread_mutex_unlock(&data->mutex_for_died);
		return (printf("Dinner end\n"), 1);
	}
	return (0);
}

void	*monitoring_loop(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		if (check_life(data) != 0)
		{
			break ;
		}
		if (data->eat_count != -1)
		{
			if (done_eating(data) != 0)
			{
				break ;
			}
		}
		usleep(500);
	}
	return (NULL);
}

void	sleeping(size_t time, t_philo *philo)
{
	size_t	start;

	start = time_now();
	while ((time_now() - start) < time)
	{
		pthread_mutex_lock(&philo->data->mutex_for_died);
		if (philo->data->died)
		{
			pthread_mutex_unlock(&philo->data->mutex_for_died);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_for_died);
		usleep(100);
	}
}
