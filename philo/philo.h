/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:39:29 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/03 01:05:19 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BOLD_RED		"\033[1;31m"
# define RESET			"\033[0m"
# define ITALIC_BLUE	"\033[3;36m"
# define ITALIC_TRAN	"\033[2;3m"
# define ITALIC			"\033[3m"
# define BOLD			"\033[1m"

# define TRUE			1
# define FALSE			0
# define FORK			"has taken a fork"
# define EAT			"is eating"
# define SLEEP			"is sleeping"
# define THINK			"is thinking"
# define DIE			"\033[1;31mdied\033[0m"
# define INV_CH			-1
# define NEG_NB			-2

typedef struct s_philo
{
	int				nb_ate;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_data
{
	bool			running;
	int				ended;
	int				nb_philo;
	int				nb_meal;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	t_philo			*philo;
	long long		start;
	pthread_mutex_t	speech;
	pthread_mutex_t	lock;
	pthread_mutex_t	lock2;
	pthread_mutex_t	lock3;
}					t_data;

void		ft_bzero(void *s, size_t len);
int			ft_ph_atoi(const char *str);
void		*ft_calloc(size_t c, size_t l);
long long	ft_timestamp(void);
void		ft_usleep(int time_to_wait);
void		ft_free(t_data *data);
int			ft_strncmp(const char *s1, const char *s2, size_t l);
int			ft_running_checker(t_data *data);
void		ft_print_action(t_data *data, char *action, int i);
int			ft_complete_av(int ac, char **av);
int			ft_init(t_data *data, int ac, char **av);
int			ft_progression_checker(t_data *data);
int			ft_print_error(t_data *data, int ac, char **av);
int			ft_check_error(t_data *data, int ac);

#endif