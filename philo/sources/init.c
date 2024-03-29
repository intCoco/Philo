/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:15:09 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/04 23:08:48 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_error(t_data *data, int ac)
{
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (ac >= 6 && data->enhanced == FALSE
			&& data->nb_meal <= 0))
		return (1);
	return (0);
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

void	ft_arg_handling(t_data *data, int ac, char **av)
{
	if (ac >= 2)
		data->nb_philo = ft_patoi(av[1]);
	if (ac >= 3)
		data->time_to_die = ft_patoi(av[2]);
	if (ac >= 4)
		data->time_to_eat = ft_patoi(av[3]);
	if (ac >= 5)
		data->time_to_sleep = ft_patoi(av[4]);
	if (ac >= 6 && ft_strcmp(av[5], "enhanced"))
		data->nb_meal = ft_patoi(av[5]);
	else
		data->nb_meal = -1;
	if (ac == 6 && !ft_strcmp(av[5], "enhanced"))
		data->enhanced = TRUE;
	if (ac == 7 && !ft_strcmp(av[6], "enhanced"))
		data->enhanced = TRUE;
}

int	ft_init(t_data *data, int ac, char **av)
{
	data->running = 1;
	ft_arg_handling(data, ac, av);
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
