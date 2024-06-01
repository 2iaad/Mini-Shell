# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:00:51 by ibouram           #+#    #+#              #
#    Updated: 2024/06/01 22:06:00 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSINGSRC = parsing/ft_split.c parsing/parsing.c parsing/quotes.c parsing/utils.c \
	parsing/add_space.c parsing/syntax_error.c parsing/Tokenizer.c parsing/lin_list.c \
	parsing/utils2.c parsing/expanding.c parsing/ft_split2.c parsing/remove_quotes.c parsing/struct.c \

EXECUTIONSRC = 

RM = rm -rf
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

PARSINGOBJS = $(PARSINGSRC:.c=.o)
EXECUTIONOBJS = $(EXECUTIONSRC:.c=.o)

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "DONE"
$(NAME): $(PARSINGOBJS)
	@$(CC) $(FLAGS)  -lreadline $^ -o $@

%.o: %.c minishell.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(PARSINGOBJS)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Clean"

re: fclean all