/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:16:23 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/05 02:01:42 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_print_arg_error(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i <= ac || i <= 5)
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
		else if (ft_patoi(av[i]) == INV_CH && ft_strcmp(av[i], "enhanced"))
			printf("%s\"%s\"%s ", BOLD_RED, av[i], RESET);
		else if (ft_patoi(av[i]) == NEG_NB || i > 5)
			printf("%s%s%s ", BOLD_RED, av[i], RESET);
		else
			printf("%s ", av[i]);
	}
}

int	ft_print_error(t_data *data, int ac, char **av)
{
	if (ft_check_error(data, ac) || (ac > 6 && ft_strcmp(av[6], "enhanced")))
	{
		if (ac > 6 && ft_strcmp(av[6], "enhanced"))
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

static void	ft_print_emoji(char *action)
{
	if (!ft_strcmp(action, EAT))
		printf(" %s", EAT_EM);
	if (!ft_strcmp(action, DIE))
		printf(" %s", DIE_EM);
	if (!ft_strcmp(action, OVER_EAT))
		printf(" %s", OVER_EAT_EM);
	if (!ft_strcmp(action, FULL))
		printf(" %s", FULL_EM);
}

static void	ft_fancy_print(t_data *data, char *action, int i)
{
	static int j;

	if (data->philo[i].nb_ate >= data->nb_meal && !ft_strcmp(action, EAT)
		&& data->nb_meal != -1)
		action = OVER_EAT;
	ft_print_emoji(action);
	if (!ft_strcmp(action, EAT) || !ft_strcmp(action, OVER_EAT))
	{
		printf(" %s%s%s%s %s", BOLD, PURPLE, action, RESET, ITALIC_TRAN);
		if ((data->philo[i].nb_ate + 1) % 10 == 1)
			printf("(for the %ist time)", data->philo[i].nb_ate + 1);
		else if ((data->philo[i].nb_ate + 1) % 10 == 2)
			printf("(for the %ind time)", data->philo[i].nb_ate + 1);
		else if ((data->philo[i].nb_ate + 1) % 10 == 3)
			printf("(for the %ird time)", data->philo[i].nb_ate + 1);
		else
			printf("(for the %ith time)", data->philo[i].nb_ate + 1);
	}
	else if (!ft_strcmp(action, FULL))
		printf(" %s %s(%i/%i)", action, ITALIC_TRAN, ++j, data->nb_philo);
	else
		printf(" %s ", action);
}

void	ft_print_action(t_data *data, char *action, int i)
{
	pthread_mutex_lock(&data->speech);
	if (ft_running_checker(data))
	{
		if (!ft_strcmp(action, DONE) && data->enhanced == TRUE)
			printf("%s%-11lld%s %s", ITALIC_BLUE, ft_timestamp() - data->start,
				RESET, action);
		else
		{
			printf("%s%-6lld%s %s%6d%s", ITALIC_BLUE, ft_timestamp()
				- data->start, RESET, BOLD, i + 1, RESET);
			if (data->enhanced == TRUE)
				ft_fancy_print(data, action, i);
			else
				printf(" %s ", action);
		}
		printf("%s\n", RESET);
	}
	pthread_mutex_unlock(&data->speech);
}
