/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:14:34 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 14:47:02 by chuchard         ###   ########.fr       */
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
