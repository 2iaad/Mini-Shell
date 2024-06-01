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
	int i = 0;
	while (i++ < 10)
	{
		if (i == 6)
		{
			continue ;
		}
		printf("i-->%d\n", i);
	}
}