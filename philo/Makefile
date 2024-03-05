# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/03/05 02:13:17 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
BLUE			= \033[38;5;111m
RED				= \033[0;31m
TRANS			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
TRANS			= \033[2m
ITALIC			= \033[3m
CLEAR			= \r\033[K
SEP				= ${TRANS}────────────────────────────────────────────────────────────────────────────\n${RESET}

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
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Compiling ${GREEN}%s${RESET}...\n${SEP}" ${notdir $<}
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@
	@sleep 0.1
	@tput cuu 3

all:			$(NAME)
	@printf "\
${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${GREEN}Welcome to my Philosophers project!${RESET}\n\n\
${BLUE}This program simulates the dining philosophers problem.${RESET}\n\n\
To compile the program, use the command:\n\
    ${PURPLE}make${RESET}\n\n\
To run the program, use the command:\n\
    ${PURPLE}./philosophers${RESET} [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ${TRANS}${ITALIC}[number_of_times_each_philosopher_must_eat]\n\
    	(you can add \"enhanced\" as an extra last parameter to run the program with a better looking display)${RESET}\n\n\
To clean the generated files, use the command:\n\
    ${PURPLE}make clean${RESET}\n\n\
To clean the generated files and the executable, use the command:\n\
    ${PURPLE}make fclean${RESET}\n\n\
To recompile the program after cleaning, use the command:\n\
    ${PURPLE}make re${RESET}\n\
${SEP}"

$(NAME): 		$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "${SEP}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project compiled ${GREEN}successfully${RESET}.\n${SEP}"
	@sleep 0.2

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}

debug:
	@make DEBUG=1 re
	@printf "${RESET}${RED}${BOLD}Compilation done with data race detection${RESET}\n"

clean:
	@for file in $(wildcard ${OBJ_DIR}*.o); do \
        printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Clearing${RESET} %s...\n${SEP}" $${file}; \
		sleep 0.1; \
		tput cuu 3; \
        ${RM} $${file}; \
    done
	@${RM} ${OBJ_DIR}
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects cleaned ${GREEN}successfully${RESET}.\n${RESET}${SEP}"

fclean: 		clean
	@tput cuu 1
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Clearing${RESET} executable...\n${SEP}"
	@${RM} ${NAME}
	@sleep 0.2
	@tput cuu 2
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.\n${RESET}${SEP}"

re: 			fclean all

.SILENT: all clean fclean re debug
.PHONY: all clean fclean re debug