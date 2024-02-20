# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/02/20 10:04:53 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRCS = 	sources/libft.c	\
		sources/init.c	\
		sources/print_manager.c	\
		sources/utils.c	\
		sources/philo.c

$(NAME) :
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean


clean :
	$(RM) $(NAME)

re : fclean all