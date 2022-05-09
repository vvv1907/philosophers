# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 09:09:32 by hcolumbu          #+#    #+#              #
#    Updated: 2022/04/27 16:45:08 by hcolumbu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

DIR = mandatory/
FILES = utils.c	init.c	processing.c	main.c

DIR_BONUS = bonus/
FILES_BONUS = 

SRCS = $(addprefix $(DIR), $(FILES))
SRCS_BONUS = $(addprefix $(DIR_BONUS), $(FILES_BONUS))

OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

HEADER = includes/philo.h
HEADER_BONUS = includes/philo_bonus.h
INCLUDES = includes/

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 #-fsanitize=thread
RM = rm -f

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus:
		@make NAME="$(NAME_BONUS)" \
		OBJS="$(OBJS_BONUS)" \
		HEADER="$(HEADER_BONUS)" all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all
