/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:16:23 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/03 08:08:02 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	inv_str(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r'
			&& *str != '\f' && *str != '\v')
			return (0);
		str++;
	}
	return (1);
}

void	ft_print_arg_error(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i <= 5)
	{
		if (i >= ac || inv_str(av[i]))
		{
			if (i == 1)
				printf("%s%s%s ", BOLD_RED, ARG_1, RESET);
			if (i == 2)
				printf("%s%s%s ", BOLD_RED, ARG_2, RESET);
			if (i == 3)
				printf("%s%s%s ", BOLD_RED, ARG_3, RESET);
			if (i == 4)
				printf("%s%s%s ", BOLD_RED, ARG_4, RESET);
			if (i == 5)
				printf("%s%s%s", ITALIC_TRAN, ARG_5, RESET);
		}
		else if (ft_ph_atoi(av[i]) == INV_CH)
			printf("%s\"%s\"%s ", BOLD_RED, av[i], RESET);
		else if (ft_ph_atoi(av[i]) == NEG_NB)
			printf("%s%s%s ", BOLD_RED, av[i], RESET);
		else
			printf("%s ", av[i]);
	}
}

int	ft_print_error(t_data *data, int ac, char **av)
{
	if (ft_check_error(data, ac) != 0 || ac > 6)
	{
		if (ac > 6)
			printf("%sToo many%s", BOLD_RED, RESET);
		else
			printf("%sInvalid or missing%s", BOLD_RED, RESET);
		printf(" arguments:\n\n%s>> %s%s ", BOLD_RED, RESET, av[0]);
		ft_print_arg_error(ac, av);
		printf("\n\n%sEvery arguments must be strictly positive numbers. "
			"Any other character will result in an error.%s\n", ITALIC, RESET);
		return (1);
	}
	return (0);
}

void	ft_print_action(t_data *data, char *action, int i)
{
	pthread_mutex_lock(&data->speech);
	if (ft_strncmp(action, DIE, 20) == 0 || ft_running_checker(data))
	{
		printf("%s%-6lld%s %s%6d%s %s\n", ITALIC_BLUE, ft_timestamp()
			- data->start, RESET, BOLD, i + 1, RESET, action);
	}
	pthread_mutex_unlock(&data->speech);
}
