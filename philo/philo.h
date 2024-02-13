/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:39:29 by chuchard          #+#    #+#             */
/*   Updated: 2024/02/13 01:34:15 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define TRUE	1
# define FALSE	0

typedef struct	s_fork
{
	int			taken;
}				t_fork;


typedef struct	s_philo
{
	int	eating;
	int	pid;
	int	sleep;
}				t_philo;

typedef struct	s_data
{
	t_philo		*philo;
	int			philo_nb;
	t_fork		*fork;
}				t_data;

#endif