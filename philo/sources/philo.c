/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:44:14 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 15:44:34 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	}
	pthread_mutex_lock(&data->lock2);
	data->ended++;
	pthread_mutex_unlock(&data->lock2);
	pthread_detach(pthread_self());
}

void	handle_single_philo_life(t_data data)
{
	printf("%s%-6lld%s %s%6d%s %s\n", ITALIC_BLUE, ft_timestamp()
		- data.start, RESET, BOLD, 1, RESET, FORK);
	ft_usleep(data.time_to_die);
	printf("%s%-6lld%s %s%6d%s %s\n", ITALIC_BLUE, ft_timestamp()
		- data.start, RESET, BOLD, 1, RESET, DIE);
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
		if (ft_ph_atoi(av[1]) == 1)
			handle_single_philo_life(data);
		else
		{
			while (++i < data.nb_philo)
				if (pthread_create(&data.philo[i].thread, NULL, \
					(void *)ft_philo, &data))
					return (printf("Threads creation went wrong\n"));
			while (ft_progression_checker(&data) == TRUE)
				usleep(1);
		}
		ft_free(&data);
		return (0);
	}
	return (1);
}
