# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/03/03 05:28:05 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
BLUE			= \033[38;5;111m
RED				= \033[0;31m
GREY			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
TRANS			= \033[2m
ITALIC			= \033[3m
CLEAR			= \r\033[K

# Executable and compilation
NAME			= philo

SRC_DIR			= ./sources/
SRCS			= 	libft.c	\
					init.c	\
					print_manager.c	\
					utils.c	\
					philo.c

OBJ_DIR			= ./objs/
OBJS			= ${addprefix ${OBJ_DIR}, ${SRCS:.c=.o}}

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Compiling ${GREEN}%s${RESET}...${GREY}" ${notdir $<}
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@

all: 			$(NAME)
	@printf "${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${GREEN}Welcome to my Philosophers project!${RESET}\n\n\
${BLUE}This program simulates the dining philosophers problem.${RESET}\n\n\
To compile the program, use the command:\n\
    ${PURPLE}make${RESET}\n\n\
To run the program, use the command:\n\
    ${PURPLE}./philosophers${RESET} [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ${TRANS}${ITALIC}[number_of_times_each_philosopher_must_eat]${RESET}\n\
    	(where each argument is a strictly positive integer)\n\n\
To clean the generated files, use the command:\n\
    ${PURPLE}make clean${RESET}\n\n\
To clean the generated files and the executable, use the command:\n\
    ${PURPLE}make fclean${RESET}\n\n\
To recompile the program after cleaning, use the command:\n\
    ${PURPLE}make re${RESET}\n\
${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

    

$(NAME): 		$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${BLUE}${BOLD}${NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"
	@clear

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}

debug:
	@make DEBUG=1 re
	@printf "${RESET}${RED}${BOLD}Compilation done with data race detection${RESET}\n"

clean:
	@${RM} ${OBJ_DIR}
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects were cleaned ${GREEN}successfully${RESET}.\n${RESET}"

fclean: 		clean
	@${RM} ${NAME}
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

re: fclean all

.SILENT: all clean fclean re debug
.PHONY: all clean fclean re debug