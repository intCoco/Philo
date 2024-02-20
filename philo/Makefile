# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/02/20 09:27:01 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Werror -Wextra -g -fsanitize=leak

RM = rm -rf

SRCS = 	libft.c	\
		init.c	\
		print_manager.c	\
		utils.c	\
		philo.c

$(NAME) :
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean


clean :
	$(RM) $(NAME)

re : fclean all