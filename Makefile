NAME = minishell

CC = cc

RM = rm -rf

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

all: $(NAME)

$(NAME) : $(OBJS) $(TOOL_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJS) $(TOOL_OBJS): %.o: %.c includes/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TOOL_OBJS)

fclean:
	$(RM) $(OBJS) $(TOOL_OBJS) $(NAME)

re:	fclean all