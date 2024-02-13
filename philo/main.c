/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:44:14 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/13 01:34:53 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[data->philo_id].personal_id = i;
		i++;
	}
	
}

void	ft_philo(t_data *data, int pid)
{
	if(data->philo_nb > 1 && data->philo[pid].sleep == FALSE \
		&& data->fork[pid].taken == 0 && data->fork[pid - 1].taken == 0)
		data
	
}

int main(int ac, char **av)
{
	t_data	*data;

	if(ac != 5 && ac != 6)	
		return  (0);
	
}