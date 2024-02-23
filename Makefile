# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 12:55:50 by tmarie            #+#    #+#              #
#    Updated: 2024/01/04 21:47:30 by tmarie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	philosophers.c		\
			philosophers2.c		\
			routine.c			\
			routine2.c			\
			routine3.c			\
			ft_atoi.c			\
			ft_itoa.c			\

SRC_H = philosophers.h

OBJS	=	${SRC:.c=.o}

NAME	=	philo

FLAGS	=	-Wall -Wextra -Werror -pthread -fsanitize=thread

all : ${NAME}

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all fclean clean re
