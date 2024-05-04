NAME = minishell

CC = cc

RM = rm -rf

FLAGS = #-fsanitize=address

SRCS =	builtins/builtins_1.c \
		builtins/identifier.c \

TOOL_SRCS = tools/mini_utils.c \
			tools/split.c \
			tools/string_utils.c \

OBJS = $(SRCS:.c=.o)
TOOL_OBJS = $(TOOL_SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(TOOL_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJS): %.o: %.c includes/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

$(TOOL_OBJS): %.o: %.c includes/tools.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TOOL_OBJS)

fclean:
	$(RM) $(OBJS) $(TOOL_OBJS) $(NAME)

re:
	fclean all