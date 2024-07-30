# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:00:51 by ibouram           #+#    #+#              #
#    Updated: 2024/07/30 03:36:49 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSINGSRC =	parsing/parsing.c parsing/quotes.c parsing/utils.c parsing/env_init.c main.c \
				parsing/add_space.c parsing/syntax_error.c parsing/Tokenizer.c parsing/lin_list.c parsing/signals.c\
				parsing/utils2.c parsing/expanding.c parsing/ft_split2.c parsing/remove_quotes.c parsing/struct.c \
				parsing/her_doc_expd.c parsing/trim_line.c parsing/lin_list2.c parsing/tokenizer2.c parsing/garbage_coll.c\
				parsing/expanding2.c parsing/struct2.c \

EXECUTIONSRC = 	execution/builtins/cd.c execution/builtins/echo.c execution/builtins/exit.c execution/builtins/caller.c \
				execution/builtins/export.c execution/builtins/pwd.c execution/builtins/unset.c execution/pipe_execute/heredoc_helper.c \
				execution/tools/equals_spliter.c execution/tools/helper_utils.c execution/pipe_execute/executer.c \
				execution/tools/lst_utils.c execution/tools/mini_utils.c execution/tools/split.c execution/tools/string_utils.c \
				execution/pipe_execute/exec_tools.c execution/pipe_execute/file_opener.c execution/pipe_execute/heredoc.c \
				execution/pipe_execute/pipex.c execution/pipe_execute/executer_helper.c execution/pipe_execute/file_helper.c \
				execution/pipe_execute/file_opener_s.c execution/tools/helper_builtins.c execution/tools/helper_export.c \
				

RM = rm -rf
NAME = minishell
CC = cc
FLAGS = -fsanitize=address -ggdb3 #-Wall -Wextra -Werror
READLINE = $(shell brew --prefix readline)

PARSINGOBJS = $(PARSINGSRC:.c=.o)
EXECUTIONOBJS = $(EXECUTIONSRC:.c=.o)
MAINOBJS = $(MAINSRC:.c=.o)

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "DONE"
$(NAME): $(PARSINGOBJS) $(EXECUTIONOBJS)
	@$(CC) $(FLAGS) -L$(READLINE)/lib -lreadline $^ -o $@


%.o: %.c minishell.h
	@$(CC) $(FLAGS) -I$(READLINE)/include -c $< -o $@

clean:
	@$(RM) $(PARSINGOBJS) $(EXECUTIONOBJS)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Clean"

re: fclean all