# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:00:51 by ibouram           #+#    #+#              #
#    Updated: 2024/05/09 06:23:54 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_split.c parcing.c quotes.c utils.c add_space.c syntax_error.c \
	Tokenizer.c lin_list.c

RM = rm -rf
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS)  -lreadline $^ -o $@

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all