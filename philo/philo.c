/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:44:14 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/20 09:57:43 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_action(t_data *data, char *action, int i);
int	ft_complete_av(int ac, char **av);
int	ft_init(t_data *data, int ac, char **av);

int	ft_progression_checker(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock2);
	while (i < data->nb_philo)
	{
		if ((ft_timestamp() - data->start)
			- data->philo[i].last_meal > data->time_to_die)
		{
			ft_print_action(data, DIE, i);
			data->running = 0;
			break ;
		}
		if (data->philo[i].nb_ate <= data->nb_meal || data->nb_meal == -1)
		{
			pthread_mutex_unlock(&data->lock2);
			return (TRUE);
		}
		ft_usleep(1);
		i++;
	}
	pthread_mutex_unlock(&data->lock2);
	return (FALSE);
}

void	ft_philo(t_data *data)
{
	static int	i;
	int			pid;

	pid = i++;
	if (pid % 2)
		ft_usleep(60);
	while (1)
	{
		pthread_mutex_lock(&data->philo[pid].l_fork);
		ft_print_action(data, FORK, pid);
		pthread_mutex_lock(data->philo[pid].r_fork);
		ft_print_action(data, FORK, pid);
		ft_print_action(data, EAT, pid);
		ft_usleep(data->time_to_eat);
		if (data->running == 0)
			break ;
		pthread_mutex_lock(&data->lock);
		data->philo[pid].last_meal = ft_timestamp() - data->start;
		data->philo[pid].nb_ate++;
		pthread_mutex_unlock(&data->lock);
		pthread_mutex_unlock(&data->philo[pid].l_fork);
		pthread_mutex_unlock(data->philo[pid].r_fork);
		ft_usleep(ft_print_action(data, SLEEP, pid));
		ft_print_action(data, THINK, pid);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = -1;
	ac = ft_complete_av(ac, av);
	ft_bzero(&data, sizeof(t_data));
	if (ft_init(&data, ac, av) == 0)
	{
		while (++i < data.nb_philo)
			if (pthread_create(&data.philo[i].thread, NULL, (void *)ft_philo,
					&data))
				return (printf("Threads creation went wrong\n"));
		while (ft_progression_checker(&data) == TRUE)
			usleep(1);
		ft_free(&data);
		return (0);
	}
	return (1);
}
