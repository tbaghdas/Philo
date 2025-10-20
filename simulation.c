#include "philo.h"

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->forks == NULL)
	{
		printf("Allocation of forks is failed");
		return (1);
	}
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	if (philos_init(data) != 0)
	{
		return (1);
	}
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Creation of thread for philosopher %d is failed\n",
				data->philos[i].id);
			destroy(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (data->philos == NULL)
	{
		printf("Allocation of philos is failed");
		return (1);
	}
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].last_time_ate = data->start;
		i++;
	}
	return (0);
}

void	join(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL) != 0)
	{
		printf("Monitor thread joining failed\n");
		// destroy(data);
		// return (1);
	}
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Philo thread joining failed\n");
			// destroy(data);
			// return (1);
		}
		i++;
	}
	// return (0);
}

int	starting_simulation(t_data *data)
{
	// pthread_mutex_lock(&data->meal_check_mutex);
	data->start = time_now();
	// pthread_mutex_unlock(&data->meal_check_mutex);
	if (create_forks(data) != 0)
	{
		destroy(data);
		return (1);
	}
	if (create_philos(data) != 0)
	{
		destroy(data);
		return (1);
	}
	if (pthread_create(&data->monitor, NULL, monitoring_loop, data) != 0)
	{
		printf("Creation of monitoring thread is failed\n");
		destroy(data);
		return (1);
	}
	join(data);
	destroy(data);
	return (0);
}
