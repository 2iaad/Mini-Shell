NAME = minishell

CC = cc

RM = rm -rf

FLAGS = 

SRCS = builtins/echo.c

TOOL_SRCS = tools/tool_1.c

OBJS = $(SRCS:.c=.o)
TOOL_OBJS = $(TOOL_OBJS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(TOOL_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJS): %.o: %.c minishell/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

$(TOOL_OBJS): %.o: %.c includes/utils.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TOOL_OBJS)

fclean:
	$(RM) $(OBJS) $(TOOL_OBJS) $(NAME)

re:
	fclean all