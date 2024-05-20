#include "includes/minishell.h"
#include "includes/tools.h"
#include <unistd.h>


void	f(char **str)
{
	int i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}


int main()
{
	int i = 0;
	char **str = ft_split("salam ana smiti ziad", ' ');

	f(str + 1);	
}