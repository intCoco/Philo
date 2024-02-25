/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:15:09 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 15:28:58 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_error(t_data *data, int ac, int *errors)
{
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (ac == 6 && data->nb_meal <= 0))
	{
		if (data->nb_philo <= 0)
			errors[0] = 1;
		if (data->time_to_die <= 0)
			errors[1] = 1;
		if (data->time_to_eat <= 0)
			errors[2] = 1;
		if (data->time_to_sleep <= 0)
			errors[3] = 1;
		if (ac == 6 && data->nb_meal <= 0)
			errors[4] = 1;
		return (1);
	}
	return (0);
}

int	ft_complete_av(int ac, char **av)
{
	while (ac < 5)
	{
		if (ac == 1)
			av[ac] = "[number_of_philosophers]";
		if (ac == 2)
			av[ac] = "[time_to_die]";
		if (ac == 3)
			av[ac] = "[time_to_eat]";
		if (ac == 4)
			av[ac] = "[time_to_sleep]";
		ac++;
	}
	return (ac);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = ft_timestamp() - data->start;
		pthread_mutex_init(&data->philo[i].l_fork, 0);
		if (i < data->nb_philo - 1)
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		else
			data->philo[i].r_fork = &data->philo[0].l_fork;
		i++;
	}
}

int	ft_init(t_data *data, int ac, char **av)
{
	data->running = 1;
	data->nb_philo = ft_ph_atoi(av[1]);
	data->time_to_die = ft_ph_atoi(av[2]);
	data->time_to_eat = ft_ph_atoi(av[3]);
	data->time_to_sleep = ft_ph_atoi(av[4]);
	if (ac == 6)
		data->nb_meal = ft_ph_atoi(av[5]);
	else
		data->nb_meal = -1;
	if (ft_print_error(data, ac, av))
		return (1);
	data->start = ft_timestamp();
	data->philo = ft_calloc(sizeof(t_philo), data->nb_philo);
	if (!data->philo)
		return (printf("Memory allocation went wrong\n"));
	pthread_mutex_init(&data->speech, 0);
	pthread_mutex_init(&data->lock, 0);
	pthread_mutex_init(&data->lock2, 0);
	pthread_mutex_init(&data->lock3, 0);
	ft_init_philo(data);
	return (0);
}
