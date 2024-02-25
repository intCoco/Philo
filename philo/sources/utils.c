/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:14:34 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 14:57:34 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time_to_wait)
{
	long long	start;

	start = ft_timestamp();
	while (ft_timestamp() - start < time_to_wait)
		usleep(1);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->nb_philo > 1)
	{
		pthread_mutex_lock(&data->lock2);
		if (data->ended == data->nb_philo)
		{
			pthread_mutex_unlock(&data->lock2);
			break ;
		}
		pthread_mutex_unlock(&data->lock2);
	}
	pthread_mutex_destroy(&data->speech);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->lock2);
	pthread_mutex_destroy(&data->lock3);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].l_fork);
		i++;
	}
	free(data->philo);
}

// Checking functions

int	ft_progression_checker(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock3);
	while (i < data->nb_philo)
	{
		if ((ft_timestamp() - data->start)
			- data->philo[i].last_meal > data->time_to_die)
		{
			ft_print_action(data, DIE, i);
			break ;
		}
		if (data->philo[i].nb_ate <= data->nb_meal || data->nb_meal == -1)
		{
			pthread_mutex_unlock(&data->lock3);
			return (TRUE);
		}
		i++;
	}
	pthread_mutex_lock(&data->lock);
	data->running = 0;
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_unlock(&data->lock3);
	return (FALSE);
}

int	ft_running_checker(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->running == 0)
	{
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	pthread_mutex_unlock(&data->lock);
	return (1);
}
