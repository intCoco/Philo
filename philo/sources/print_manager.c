/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:16:23 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/25 15:28:41 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_arg_error(int ac, char **av, int *errors)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (errors[i - 1] == 1 || i >= 6)
			printf("%s%s%s ", BOLD_RED, av[i], RESET);
		else
			printf("%s ", av[i]);
	}
}

int	ft_print_error(t_data *data, int ac, char **av)
{
	int	*errors;

	errors = ft_calloc(ac - 1, sizeof(int));
	if (ft_check_error(data, ac, errors) != 0 || ac > 6)
	{
		if (ac > 6)
			printf("%sToo many%s", BOLD_RED, RESET);
		else
			printf("%sInvalid or missing%s", BOLD_RED, RESET);
		printf(" arguments:\n\n%s>> %s%s ", BOLD_RED, RESET, av[0]);
		ft_print_arg_error(ac, av, errors);
		if (ac < 6)
			printf("%s[number_of_times_each_philosopher_must_eat]%s",
				ITALIC_TRAN, RESET);
		printf("\n\n%sEvery arguments must be strictly positive numbers. "
			"Any other character will result in an error.%s\n", ITALIC, RESET);
		free(errors);
		return (1);
	}
	free(errors);
	return (0);
}

void	ft_print_action(t_data *data, char *action, int i)
{
	if (ft_running_checker(data))
	{
		pthread_mutex_lock(&data->speech);
		printf("%s%-6lld%s %s%6d%s %s\n", ITALIC_BLUE, ft_timestamp()
			- data->start, RESET, BOLD, i + 1, RESET, action);
		pthread_mutex_unlock(&data->speech);
	}
}
