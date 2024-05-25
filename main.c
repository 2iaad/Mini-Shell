#include "includes/minishell.h"
#include "includes/tools.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


// void	f(char **str)
// {
// 	int i = 0;
// 	while (str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// }


int main()
{
	char *str;

	while (1)
	{
		str = readline("----->>");
		printf("%s\n", str);
	}
}