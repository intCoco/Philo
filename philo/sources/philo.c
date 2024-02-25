/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:44:14 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 14:50:44 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_action(t_data *data, char *action, int i);
int		ft_complete_av(int ac, char **av);
int		ft_init(t_data *data, int ac, char **av);

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

int	ft_fork_picking(t_data *data, int pid)
{
	if (pid % 2)
		pthread_mutex_lock(&data->philo[pid].l_fork);
	else
		pthread_mutex_lock(data->philo[pid].r_fork);
	ft_print_action(data, FORK, pid);
	if (pid % 2)
	{
		if (pthread_mutex_lock(data->philo[pid].r_fork) != 0)
		{
			pthread_mutex_unlock(&data->philo[pid].l_fork);
			return (0);
		}
	}
	else
	{
		if (pthread_mutex_lock(&data->philo[pid].l_fork) != 0)
		{
			pthread_mutex_unlock(data->philo[pid].r_fork);
			return (0);
		}
	}
	ft_print_action(data, FORK, pid);
	return (1);
}

void	ft_eat(t_data *data, int pid)
{
	if (data->nb_philo == 1)
	{
		ft_print_action(data, FORK, pid);
		ft_usleep(data->time_to_die + 10);
		return ;
	}
	if (!ft_fork_picking(data, pid))
		return ;
	ft_print_action(data, EAT, pid);
	pthread_mutex_lock(&data->lock3);
	data->philo[pid].last_meal = ft_timestamp() - data->start;
	data->philo[pid].nb_ate++;
	pthread_mutex_unlock(&data->lock3);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->philo[pid].l_fork);
	pthread_mutex_unlock(data->philo[pid].r_fork);
}

void	ft_philo(t_data *data)
{
	static int	i;
	int			pid;

	pthread_mutex_lock(&data->lock2);
	pid = i++;
	pthread_mutex_unlock(&data->lock2);
	if (pid % 2)
		ft_usleep(60);
	while (1)
	{
		ft_eat(data, pid);
		if (ft_running_checker(data) == 0)
			break ;
		ft_print_action(data, SLEEP, pid);
		ft_usleep(data->time_to_sleep);
		if (ft_running_checker(data) == 0)
			break ;
		ft_print_action(data, THINK, pid);
		ft_usleep(data->time_to_sleep);
	}
	pthread_mutex_lock(&data->lock2);
	data->ended++;
	pthread_mutex_unlock(&data->lock2);
	pthread_detach(pthread_self());
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
