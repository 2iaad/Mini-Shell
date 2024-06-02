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

<<<<<<< HEAD
FLAGS = -lreadline -g -fsanitize=address

SRCS =	builtins/echo.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/identifier.c \
		builtins/exit.c \

TOOL_SRCS = tools/mini_utils.c \
			tools/split.c \
			tools/string_utils.c \
			tools/lst_utils.c \
			tools/equals_spliter.c \
			tools/helper_utils.c \

OBJS = $(SRCS:.c=.o)
TOOL_OBJS = $(TOOL_SRCS:.c=.o)
=======
PARSINGOBJS = $(PARSINGSRC:.c=.o)
EXECUTIONOBJS = $(EXECUTIONSRC:.c=.o)
>>>>>>> origin/idder

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "DONE"
$(NAME): $(PARSINGOBJS)
	@$(CC) $(FLAGS)  -lreadline $^ -o $@

<<<<<<< HEAD
$(NAME) : $(OBJS) $(TOOL_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJS) $(TOOL_OBJS): %.o: %.c includes/minishell.h
	$(CC) $(FLAGS) -c $< -o $@
=======
%.o: %.c minishell.h
	@$(CC) $(FLAGS) -c $< -o $@
>>>>>>> origin/idder

clean:
	@$(RM) $(PARSINGOBJS)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Clean"

<<<<<<< HEAD
re:	fclean all
=======
re: fclean all
>>>>>>> origin/idder
