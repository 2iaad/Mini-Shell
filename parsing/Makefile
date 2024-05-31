# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:00:51 by ibouram           #+#    #+#              #
#    Updated: 2024/05/31 21:53:26 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_split.c parsing.c quotes.c utils.c add_space.c syntax_error.c \
	Tokenizer.c lin_list.c utils2.c expanding.c ft_split2.c remove_quotes.c struct.c \

RM = rm -rf
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJS = $(SRC:.c=.o)

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "DONE"
$(NAME): $(OBJS)
	@$(CC) $(FLAGS)  -lreadline $^ -o $@

%.o: %.c minishell.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Clean"

re: fclean all